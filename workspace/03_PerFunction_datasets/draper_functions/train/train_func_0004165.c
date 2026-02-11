printTest(bool success, const std::string& expected_result, const std::string& actual_result)
{
	if ( sqlOutput )
	{
		std::cout << "INSERT INTO \"" << normalize_filename(*curr_file) << "\" VALUES ("
		          << caseCount << ", "
		          << testCount << ", "
		          << "'" << opSignature << "', "
		          << "'" << curr_case_desc << "', ";

		std::string geomOut;

		if ( gA ) {
			std::cout << "'" << printGeom(gA) << "', ";
		} else {
			std::cout << "NULL, ";
		}

		if ( gB ) {
			std::cout << "'" << printGeom(gB) << "', ";
		} else {
			std::cout << "NULL, ";
		}

		std::cout << "'" << expected_result << "', "
		          << "'" << actual_result << "', ";

		if ( success ) std::cout << "'t'";
		else std::cout << "'f'";

		std::cout << ");" << std::endl;
	}

	else
	{
		std::cout << *curr_file <<":";
		std::cout << " case" << caseCount << ":";
		std::cout << " test" << testCount << ": "
			<< opSignature;
		std::cout << ": " << (success?"ok.":"failed.")<<std::endl;

		std::cout << "\tDescription: " << curr_case_desc << std::endl;


		if ( gA ) {
			std::cout << "\tGeometry A: ";
			printGeom(std::cout, gA);
			std::cout << std::endl;
		}

		if ( gB ) {
			std::cout << "\tGeometry B: ";
			printGeom(std::cout, gB);
			std::cout << std::endl;
		}

		std::cout << "\tExpected result: "<<expected_result<<std::endl;
		std::cout << "\tObtained result: "<<actual_result<<std::endl;
		std::cout <<std::endl;
	}
}
