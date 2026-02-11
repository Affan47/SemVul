deleteBrokenAfter(bool bClearFirst,UT_sint32 iOldBottom)
{
	if(!containsNestedTables())
	{
		return;
	}

	UT_sint32 i = 0;
	fp_Container * pCon;
	for(i=0; i< countCons(); i++)
	{
		pCon = static_cast<fp_Container *>(getNthCon(i));
		if (pCon->getContainerType() == FP_CONTAINER_TABLE)
		{
			fp_TableContainer * pTab = static_cast<fp_TableContainer*>(pCon);
			UT_sint32 iYTab = getY() + pTab->getY();
			if (iYTab > iOldBottom)
			{
				UT_ASSERT(!pTab->getMasterTable());
				pTab->deleteBrokenAfter(bClearFirst);
			}
			else if (iYTab + pTab->getTotalTableHeight() < iOldBottom)
			{
				continue;
			}
			else
			{
				while(pTab)
				{
					if (iYTab + pTab->getYBreak() >= iOldBottom)
					{
						break;
					}
					pTab = static_cast<fp_TableContainer*>(pTab->getNext());
				}

				if(pTab && pTab->getPrev())
				{
					pTab = static_cast<fp_TableContainer*>(pTab->getPrev());
					pTab->deleteBrokenAfter(bClearFirst);
				}
			}
		}
	}
}
