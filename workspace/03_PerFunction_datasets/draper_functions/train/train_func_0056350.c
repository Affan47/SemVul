testMacroAssertZeros_good(void )
{
	float values[100];
	memset(values,0,sizeof(values));
	try {
		SVUT_ASSERT_ZEROS(values,100);
	} catch (svutExAssertFailZeros &) {
		CPPUNIT_FAIL("Thow unexpected svutExAssertFailZeros exception.");
	} catch (...) {
		CPPUNIT_FAIL("Thow unexpected exception.");
	}
}
