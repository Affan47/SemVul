pasteFromLocalTo(PT_DocPosition pos)
{
	UT_return_if_fail(m_pLocalBuf);

	_saveAndNotifyPieceTableChange();
	m_pDoc->disableListUpdates();
	m_pDoc->beginUserAtomicGlob();
	m_pDoc->setDoingPaste();
	setCursorWait();
	m_pDoc->setDontImmediatelyLayout(true);

	_pasteFromLocalTo(pos);
	clearCursorWait();
	m_pDoc->clearDoingPaste();
	m_pDoc->setDontImmediatelyLayout(false);


	m_pDoc->enableListUpdates();
	m_pDoc->updateDirtyLists();


	_restorePieceTableState();
	_generalUpdate();
	m_pDoc->endUserAtomicGlob();


	_charMotion(true, 0);
	_fixInsertionPointCoords();
	if (isSelectionEmpty())
	{
		_ensureInsertionPointOnScreen();
	}
	notifyListeners(AV_CHG_MOTION | AV_CHG_HDRFTR);
}
