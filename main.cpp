
#include <iostream>

#include "Register.h"
#include "Processor.h"

#include "CommandParser.h"
#include "FileStreamController.h"

#include "BinaryOperations.h"
#include "UnaryOperations.h"

using std::cout;

int main() {

	BinaryOperations<Register<8>, Register<8>, Register<8>> bin;
	UnaryOperations<Register<8>, Register<8>> un;
	bin.insert("add", [](Register<8> ob1, Register<8> ob2) { return ob1 + ob2; });
	bin.insert("substract", [](Register<8> ob1, Register<8> ob2) { return ob1 - ob2; });
	bin.insert("or", [](Register<8> ob1, Register<8> ob2) { return ob1 | ob2; });
	bin.insert("and", [](Register<8> ob1, Register<8> ob2) { return ob1 & ob2; });
	bin.insert("xor", [](Register<8> ob1, Register<8> ob2) { return ob1 ^ ob2; });
	un.insert("invert", [](Register<8> ob) { return ob.invert(); });
	
	FileStreamController<std::vector<string>> controller("input.txt", "output.txt");
	Processor<8, 5> pros(CommandParser{}, un, bin);
	auto res = controller.read();
	auto vec = res.value();
	auto f = [](auto pros, auto vec) -> void {
		for (auto& x : vec) {
			pros.addCommand(x);
			std::cout << pros;
			pros.doCommand();
			std::cout << pros << '\n';
		}
	};

	f(pros, vec);
	return 0;

}