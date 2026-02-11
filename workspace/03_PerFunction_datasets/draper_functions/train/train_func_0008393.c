getFirstLineInColumn(fp_Column * pCol)
{
	fp_TableContainer * pTab = NULL;
	fp_TableContainer * pBroke = NULL;
	fp_CellContainer * pCell = NULL;
	if(!isThisBroken())
	{
		pTab = this;
	}
	else
	{
		pBroke = this;
		pTab = getMasterTable();
	}
	pCell = static_cast<fp_CellContainer *>(pTab->getNthCon(0));
	if(!pBroke)
	{
		while(pCell)
		{
			fp_Container * pFirst = static_cast<fp_Container *>(pCell->getNthCon(0));
			while(pFirst && pCell->getColumn(pFirst) != static_cast<fp_VerticalContainer *>(pCol))
			{
				pFirst = static_cast<fp_Container *>(pFirst->getNext());
			}
			if(pFirst)
			{
				if(pFirst->getContainerType() == FP_CONTAINER_LINE)
				{
					return static_cast<fp_Line *>(pFirst);
				}
				if(pFirst->getContainerType() == FP_CONTAINER_TABLE)
				{
					return static_cast<fp_TableContainer *>(pFirst)->getFirstLineInColumn(pCol);
				}
				UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
				return NULL;
			}
			pCell = static_cast<fp_CellContainer *>(pCell->getNext());
		}
		return NULL;
	}
	while(pCell)
	{
		if(pCell->doesOverlapBrokenTable(pBroke))
		{
			fp_Container * pFirst = static_cast<fp_Container *>(pCell->getNthCon(0));
			while(pFirst && pCell->getColumn(pFirst) != static_cast<fp_VerticalContainer *>(pCol))
			{
				pFirst =  static_cast<fp_Container *>(pFirst->getNext());
			}
			if(pFirst)
			{
				if(pFirst->getContainerType() == FP_CONTAINER_LINE)
				{
					return static_cast<fp_Line *>(pFirst);
				}
				if(pFirst->getContainerType() == FP_CONTAINER_TABLE)
				{
					return static_cast<fp_TableContainer *>(pFirst)->getFirstLineInColumn(pCol);
				}
				UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
				return NULL;
			}
		}
		pCell =  static_cast<fp_CellContainer *>(pCell->getNext());
	}
	return NULL;
}
