_doInsertTOCTabRun(PT_BlockOffset blockOffset)
{
	fp_Run* pNewRun = new fp_TabRun(this,blockOffset, 1);
	UT_ASSERT(pNewRun);
	static_cast<fp_TabRun *>(pNewRun)->setTOCTab();
	return _doInsertRun(pNewRun);
}
