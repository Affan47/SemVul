registerFlatTestCaseMethod(const char* testCaseName, const char* functionName, svUnitTest::svutTestMethodPtr methodPtr,const svUnitTest::svutCodeLocation & location)
{
	if (globalFlatTestRegistry == NULL)
		initGlobalFlatTestRegistry();
	svutFlatRegistryEntry entry;
	entry.testCaseName = testCaseName;
	entry.testName = functionName;
	entry.methodPtr = methodPtr;
	entry.fixtureTest = NULL;
	entry.location = location;
	globalFlatTestRegistry->push_back(entry);
	return true;
}
