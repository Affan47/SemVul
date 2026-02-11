setHeight(UT_sint32 iHeight)
{
	xxx_UT_DEBUGMSG(("cell: Height was %d \n",getHeight()));
	if ((iHeight == getHeight()) || (iHeight== 0))
	{
		return;
	}
	clearScreen();
	fp_TableContainer * pTab = static_cast<fp_TableContainer *>(getContainer());
	if(pTab && getBottomAttach() == pTab->getNumRows())
	{
		fp_CellContainer * pCell = pTab->getCellAtRowColumn(pTab->getNumRows() -1,0);
		while(pCell)
		{
			pCell->clearScreen();
			pCell->getSectionLayout()->setNeedsRedraw();
			pCell->getSectionLayout()->markAllRunsDirty();
			pCell = static_cast<fp_CellContainer *>(pCell->getNext());
		}
	}
	fp_VerticalContainer::setHeight(iHeight);
	xxx_UT_DEBUGMSG(("cell: Height set to %d \n",getHeight()));
	fl_SectionLayout * pSL = getSectionLayout();
	pSL = static_cast<fl_SectionLayout *>(pSL->myContainingLayout());
	UT_ASSERT(pSL->getContainerType() == FL_CONTAINER_TABLE);
	static_cast<fl_TableLayout *>(pSL)->setDirty();
	static_cast<fl_TableLayout *>(pSL)->setHeightChanged(this);
}
