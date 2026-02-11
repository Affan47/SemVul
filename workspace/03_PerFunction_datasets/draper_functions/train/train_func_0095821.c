getLastLineInColumn(fp_Column * pCol)
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
	UT_return_val_if_fail(pTab,NULL);
	if(pTab->countCons() == 0)
	{
		return NULL;
	}
	pCell = static_cast<fp_CellContainer *>(pTab->getNthCon(pTab->countCons()-1));
	if(!pBroke)
	{
		while(pCell)
		{
			if(pCell->countCons() > 0)
			{
				fp_Container * pLast = static_cast<fp_Container *>(pCell->getNthCon(pCell->countCons()-1));
				while(pLast && pCell->getColumn(pLast) != static_cast<fp_VerticalContainer *>(pCol))
				{
					pLast = static_cast<fp_Container *>(pLast->getPrev());
				}
				if(!pLast)
					return NULL;
				if(pLast->getContainerType() == FP_CONTAINER_LINE)
				{
					return static_cast<fp_Line *>(pLast);
				}
				if(pLast->getContainerType() == FP_CONTAINER_TABLE)
				{
					return static_cast<fp_TableContainer *>(pLast)->getLastLineInColumn(pCol);
				}
				UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
				return NULL;
			}
			pCell = static_cast<fp_CellContainer *>(pCell->getPrev());
		}
		return NULL;
	}
	while(pCell)
	{
		if(pCell->doesOverlapBrokenTable(pBroke) && (pCell->countCons() > 0))
		{
			fp_Container * pLast = static_cast<fp_Container *>(pCell->getNthCon(pCell->countCons()-1));
			while(pLast && pCell->getColumn(pLast) != static_cast<fp_VerticalContainer *>(pCol))
			{
				pLast =  static_cast<fp_Container *>(pLast->getNext());
			}
			if(pLast)
			{
				if(pLast->getContainerType() == FP_CONTAINER_LINE)
				{
					return static_cast<fp_Line *>(pLast);
				}
				if(pLast->getContainerType() == FP_CONTAINER_TABLE)
				{
					return static_cast<fp_TableContainer *>(pLast)->getLastLineInColumn(pCol);
				}
				UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
				return NULL;
			}
		}
		pCell =  static_cast<fp_CellContainer *>(pCell->getPrev());
	}
	return NULL;
}
