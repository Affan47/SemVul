suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DateTimeTest");

	CppUnit_addTest(pSuite, DateTimeTest, testTimestamp);
	CppUnit_addTest(pSuite, DateTimeTest, testJulian);
	CppUnit_addTest(pSuite, DateTimeTest, testGregorian);
	CppUnit_addTest(pSuite, DateTimeTest, testConversions);
	CppUnit_addTest(pSuite, DateTimeTest, testStatics);
	CppUnit_addTest(pSuite, DateTimeTest, testCalcs);
	CppUnit_addTest(pSuite, DateTimeTest, testAMPM);
	CppUnit_addTest(pSuite, DateTimeTest, testRelational);
	CppUnit_addTest(pSuite, DateTimeTest, testArithmetics);
	CppUnit_addTest(pSuite, DateTimeTest, testSwap);

	CppUnit_addTest(pSuite, DateTimeTest, testUsage);
	CppUnit_addTest(pSuite, DateTimeTest, testSetYearDay);
	CppUnit_addTest(pSuite, DateTimeTest, testIsValid);
	CppUnit_addTest(pSuite, DateTimeTest, testDayOfWeek);
	CppUnit_addTest(pSuite, DateTimeTest, testIncrementDecrement);
	CppUnit_addTest(pSuite, DateTimeTest, testUTC);

	return pSuite;
}
