openTestCase(const svUnitTest::svutTestCase& testCase)
{
	char buffer[1024];
	sprintf(buffer,"openTestCase(%s)",testCase.getName().c_str());
	event.push_back(buffer);
}
