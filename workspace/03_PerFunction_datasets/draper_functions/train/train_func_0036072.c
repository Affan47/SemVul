doclistener_insertFmtMark(const PX_ChangeRecord_FmtMark* pcrfm)
{
	_assertRunListIntegrity();

	PT_BlockOffset blockOffset = pcrfm->getBlockOffset();

	xxx_UT_DEBUGMSG(("Edit:InsertFmtMark [blockOffset %ld]\n",blockOffset));

	fp_FmtMarkRun * pNewRun = new fp_FmtMarkRun(this, blockOffset);
	UT_ASSERT(pNewRun);
	_doInsertRun(pNewRun);


	FV_View* pView = getView();
	if (pView && (pView->isActive() || pView->isPreview()))
		pView->_setPoint(pcrfm->getPosition());
	if(pView)
		pView->updateCarets(pcrfm->getPosition(),0);

	if (pView)
	{
		pView->_resetSelection();


	}
	m_iNeedsReformat = blockOffset;
	format();
	_assertRunListIntegrity();
	return true;
}
