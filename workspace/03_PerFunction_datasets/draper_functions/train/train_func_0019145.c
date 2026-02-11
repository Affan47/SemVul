isPointBeforeListLabel(void) const
{


	fl_BlockLayout * pBlock = getCurrentBlock();
	bool bBefore = true;
	if(pBlock->isListItem() == false)
	{
		return false;
	}


	PT_DocPosition pos = getPoint();
	UT_sint32 xPoint;
	UT_sint32 yPoint;
	UT_sint32 iPointHeight;
	UT_sint32 xPoint2;
	UT_sint32 yPoint2;
	bool   bDirection;

	fp_Run* pRun = pBlock->findPointCoords(pos, m_bPointEOL, xPoint, yPoint, xPoint2, yPoint2, iPointHeight, bDirection);
	pRun = pRun->getPrevRun();
	while(pRun != NULL && bBefore == true)
	{
		if(pRun->getType()== FPRUN_FIELD)
		{
			fp_FieldRun * pFRun = static_cast<fp_FieldRun *>(pRun);
			if (pFRun->getFieldType() == FPFIELD_list_label)
			{
				bBefore = false;
			}
		}
		pRun = pRun->getPrevRun();
	}
	return bBefore;
}
