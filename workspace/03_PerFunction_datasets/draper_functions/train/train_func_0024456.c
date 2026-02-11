printErrors(std::ostream& stream)
{
	if (testErrors() != 0)
	{
		stream << "\n";

		if (testErrors() == 1)
			stream << "There was " << testErrors() << " error: " << std::endl;
		else
			stream << "There were " << testErrors() << " errors: " << std::endl;

		int i = 1;
		for (std::vector<TestFailure*>::iterator it = errors().begin(); it != errors().end(); ++it)
		{
			TestFailure* failure = *it;
			CppUnitException* e = failure->thrownException();

			stream << std::setw(2) << i
			       << ": "
			       << failure->failedTest()->toString() << "\n"
			       << "    \"" << (e ? e->what() : "") << "\"\n"
			       << "    in \""
			       << (e ? e->fileName() : std::string())
			       << "\", line ";
			if (e == 0)
			{
				stream << "0";
			}
			else
			{
				stream << e->lineNumber();
				if (e->data2LineNumber() != CppUnitException::CPPUNIT_UNKNOWNLINENUMBER)
				{
					stream << " data lines " << e->data1LineNumber()
                                               << ", " << e->data2LineNumber();
				}
				else if (e->data1LineNumber() != CppUnitException::CPPUNIT_UNKNOWNLINENUMBER)
				{
					stream << " data line " << e->data1LineNumber();
				}
			}
			stream << "\n";
			i++;
		}
	}
}
