cmdPasteSelectionAt(UT_sint32 xPos, UT_sint32 yPos)
{


	m_pDoc->beginUserAtomicGlob();


	_saveAndNotifyPieceTableChange();

	if (!isSelectionEmpty())
		m_pApp->cacheCurrentSelection(this);
	cmdCopy(false);
	warpInsPtToXY(xPos,yPos,true);
	_doPaste(false, true);
	m_pApp->cacheCurrentSelection(NULL);


	_restorePieceTableState();
	_fixInsertionPointCoords();
	_ensureInsertionPointOnScreen();

	m_pDoc->endUserAtomicGlob();
	m_prevMouseContext =  EV_EMC_TEXT;
	notifyListeners(AV_CHG_ALL);
}
