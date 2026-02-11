_doInsertTabRun(PT_BlockOffset blockOffset)
{
	fp_Run * pNewRun = NULL;
	if(!isContainedByTOC() || !m_bPrevListLabel)
	{
		pNewRun = new fp_TabRun(this,blockOffset, 1);
	}
	else
	{
		xxx_UT_DEBUGMSG(("Insert dummy in place of TAB at %d \n",blockOffset));
		pNewRun = new fp_DummyRun(this,blockOffset);
	}
	UT_ASSERT(pNewRun);

	return _doInsertRun(pNewRun);
}
