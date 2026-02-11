isTabListAheadPoint(void) const
{


	PT_DocPosition cpos = getPoint();

	bool bEOL = false;
	UT_uint32 iPointHeight;
	UT_sint32 xPoint, yPoint, xPoint2, yPoint2;
	bool   bDirection;

	fl_BlockLayout* pBlock;
	fp_Run* pRun;
	_findPositionCoords(cpos, bEOL, xPoint, yPoint, xPoint2, yPoint2, iPointHeight, bDirection, &pBlock, &pRun);

	if (!pBlock)
	{
		return false;
	}


	while (pRun && (pRun->getType() == FPRUN_FMTMARK))
	{
		pRun = pRun->getNextRun();
	}

	if (!pRun || pRun->getType() != FPRUN_FIELD)
	{
		return false;
	}

	const fp_FieldRun * pFRun = static_cast<const fp_FieldRun *>(pRun);
	if(pFRun->getFieldType() != FPFIELD_list_label)
	{
		return false;
	}

	pRun = pRun->getNextRun();
	while (pRun && (pRun->getType()== FPRUN_FMTMARK))
	{
		pRun = pRun->getNextRun();
	}
	if (!pRun || pRun->getType() != FPRUN_TAB)
	{
		return false;
	}

	return true;
}
