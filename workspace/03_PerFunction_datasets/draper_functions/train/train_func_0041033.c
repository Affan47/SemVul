setUp(void)
{
	listener = new svutListenerSummary();
	testCase = new UnitTestMockTestCase2();
	testCase->useTests(UnitTestMockTestCase2::REGISTER_ALL);
}
