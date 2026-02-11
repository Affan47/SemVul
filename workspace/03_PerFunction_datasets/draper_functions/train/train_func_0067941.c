delTo(FV_DocPos dp)
{
	PT_DocPosition iPos = _getDocPos(dp);
	PT_DocPosition iPoint = getPoint();

	if (iPos == iPoint)
	{
		return;
	}


	_saveAndNotifyPieceTableChange();

	_extSelToPos(iPos);

	bool bCaretLeft = false;
	if(isMarkRevisions() && iPos < iPoint)
	{

		bCaretLeft = true;
	}

	_deleteSelection(NULL, false, bCaretLeft);


	_restorePieceTableState();

	_generalUpdate();
	_fixInsertionPointCoords();

}
