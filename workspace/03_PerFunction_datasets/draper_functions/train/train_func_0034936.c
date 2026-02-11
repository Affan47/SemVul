getNumColumnsInSelection(void) const
{
	UT_GenericVector<fl_BlockLayout *> vecBlocks;
	getBlocksInSelection(&vecBlocks);
	UT_sint32 i =0;
	UT_sint32 iNumCols = 0;
	UT_sint32 iCurCol = -1;
	fl_BlockLayout * pBlock = NULL;
	fl_CellLayout * pCell = NULL;
	fp_CellContainer * pCellCon = NULL;
	for(i=0; i< vecBlocks.getItemCount();i++)
	{
		pBlock = vecBlocks.getNthItem(i);
		if(pBlock->myContainingLayout()->getContainerType() != FL_CONTAINER_CELL)
		{
			return 0;
		}
		pCell = static_cast<fl_CellLayout *>(pBlock->myContainingLayout());
		pCellCon = static_cast<fp_CellContainer *>(pCell->getFirstContainer());
		if(pCellCon == NULL)
		{
			return 0;
		}
		if(pCellCon->getLeftAttach() > iCurCol)
		{
			iNumCols++;
			iCurCol = pCellCon->getLeftAttach();
		}
	}
	return iNumCols;
}
