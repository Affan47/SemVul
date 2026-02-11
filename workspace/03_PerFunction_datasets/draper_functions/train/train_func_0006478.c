suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("CoreTestSuite");

	pSuite->addTest(CoreTest::suite());
	pSuite->addTest(AutoPtrTest::suite());
	pSuite->addTest(SharedPtrTest::suite());
	pSuite->addTest(AutoReleasePoolTest::suite());
	pSuite->addTest(ByteOrderTest::suite());
	pSuite->addTest(StringTest::suite());
	pSuite->addTest(StringTokenizerTest::suite());
	pSuite->addTest(FPETest::suite());
	pSuite->addTest(RegularExpressionTest::suite());
	pSuite->addTest(NDCTest::suite());
	pSuite->addTest(NumberFormatterTest::suite());
	pSuite->addTest(NumberParserTest::suite());
	pSuite->addTest(DynamicFactoryTest::suite());
	pSuite->addTest(MemoryPoolTest::suite());
	pSuite->addTest(AnyTest::suite());
	pSuite->addTest(DynamicAnyTest::suite());
	pSuite->addTest(FormatTest::suite());
	pSuite->addTest(TuplesTest::suite());
	pSuite->addTest(NamedTuplesTest::suite());
	pSuite->addTest(TypeListTest::suite());

	return pSuite;
}
