#ifndef EASYLANG_VMTESTS_H
#define EASYLANG_VMTESTS_H

#define CATCH_CONFIG_RUNNER
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>

#include "../include/Catch.h"
#include "../include/Vm.h"

using namespace std;

TEST_CASE("VM If statement tests") {
	vm_system vm;

	/*
	int status;
	if (2018 - 1985 == 33)
	status = 1;
	else
	status = 0;
	*/

	std::vector<size_t> codes{
		iPUSH, 2018,
		iPUSH, 1985,
		iSUB,
		iPUSH, 33,
		iEQ,
		iJIF, 13,
		iPUSH, 1,
		iHALT,
		iPUSH, 0,
		iHALT
	};
	vm.execute(&codes[0], codes.size());

	REQUIRE(vm.getUInt() == 1);
}

TEST_CASE("VM For statement tests") {
	vm_system vm;

	// int total = 100;
	// for (int i = 0; i < total; ++i) { }

	std::vector<size_t> codes{
		iPUSH, 100, // total
		iCALL, 5, // jump and create new stack
		iHALT,

		// Init variables
		iSTORE, 0, // save total
		iLOAD, 0, // get total to stack
		iPUSH, 0, // i = 0
		iSTORE, 1, // save i
		iLOAD, 1,
		iGT,
		iJIF, 29,
		iLOAD, 0,
		iLOAD, 1,
		iINC, // ++i
		iSTORE, 1,
		iLOAD, 1,
		iJMP, 15, // loop
		iLOAD, 1, // return i value
		iRETURN // clear stack
	};
	vm.execute(&codes[0], codes.size());

	REQUIRE(vm.getUInt() == 100);
}

#endif //EASYLANG_VMTESTS_H