findPrev(bool& bDoneEntireDocument)
{
	if (!isSelectionEmpty())
	{
		_clearSelection();
	}

	UT_uint32* pPrefix = _computeFindPrefix(m_sFind);
	bool bRes = _findPrev(pPrefix, bDoneEntireDocument);
	FREEP(pPrefix);

	if (isSelectionEmpty())
	{
		_updateInsertionPoint();
	}
	else
	{
		_ensureInsertionPointOnScreen();
		_drawSelection();
	}

	notifyListeners(AV_CHG_MOTION);
	return bRes;
}
