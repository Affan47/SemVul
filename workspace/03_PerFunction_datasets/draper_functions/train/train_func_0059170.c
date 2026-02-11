testIrrString(void)
{
	bool allExpected = true;

	logTestString("Test stringc\n");
	{

		core::stringc empty;
		assert_log(empty.size()==0);
		assert_log(empty[0]==0);
		assert_log(empty.c_str()!=0);
		assert_log(*(empty.c_str())==0);

		empty = "Test";
		assert_log(empty.size()==4);
		assert_log(empty[0]=='T');
		assert_log(empty[3]=='t');
		assert_log(*(empty.c_str())=='T');

		empty = "";
		assert_log(empty.size()==0);
		assert_log(empty[0]==0);
		assert_log(*(empty.c_str())==0);
	}
	logTestString("Test stringw\n");
	{
		core::stringw empty;
		assert_log(empty.size()==0);
		assert_log(empty[0]==0);
		assert_log(empty.c_str()!=0);
		assert_log(*(empty.c_str())==0);
		empty = L"Test";
		assert_log(empty.size()==4);
		assert_log(empty[0]==L'T');
		assert_log(empty[3]=='t');
		assert_log(*(empty.c_str())==L'T');
		empty = L"";
		assert_log(empty.size()==0);
		assert_log(empty[0]==0);
		assert_log(*(empty.c_str())==0);
		assert_log(allExpected &= testSplit());
	}
	allExpected &= testAppendStringc();

	logTestString("Test io::path\n");
	{

		io::path myPath;
		myPath = "Some text";
	}

	logTestString("Test self assignment\n");
	allExpected &= testSelfAssignment();

	logTestString("test fast alloc\n");
	allExpected &= testFastAlloc();

	logTestString("test replace\n");
	allExpected &= testReplace();

	logTestString("test make_lower and make_uppers\n");
	allExpected &= testLowerUpper();

	logTestString("test find functions\n");
	allExpected &= testFindFunctions();

	if(allExpected)
		logTestString("\nAll tests passed\n");
	else
		logTestString("\nFAIL!\n");

	return allExpected;
}
