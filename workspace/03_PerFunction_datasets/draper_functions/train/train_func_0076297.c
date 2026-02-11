getBrokenTable(fp_Container * pCon) const
{
	fp_TableContainer * pMaster = static_cast<fp_TableContainer *>(getContainer());
	if(!pMaster)
	{
		return NULL;
	}
	fp_TableContainer * pBroke = pMaster->getFirstBrokenTable();
	if (!pBroke)
	{
		return pMaster;
	}

	UT_sint32 yPos = getY() + pCon->getY() + 1;
	while(pBroke && (pBroke->getYBottom() < yPos))
    {
		pBroke = static_cast<fp_TableContainer *>(pBroke->getNext());
	}

	return ((pBroke) ? pBroke : pMaster);
}
