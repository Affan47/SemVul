testIrrArray(void)
{
	bool allExpected = true;

	logTestString("crashTestFastAlloc\n");
	crashTestFastAlloc();
	allExpected &= testSelfAssignment();
	allExpected &= testSwap();

	if(allExpected)
		logTestString("\nAll tests passed\n");
	else
		logTestString("\nFAIL!\n");

	return allExpected;
}
