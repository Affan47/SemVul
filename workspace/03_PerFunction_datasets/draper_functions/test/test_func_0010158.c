_addBlockInVec(fl_BlockLayout * pBlock, UT_UTF8String & sStyle)
{

	PT_DocPosition posNew = pBlock->getPosition();
	TOCEntry * pEntry = NULL;
	fl_BlockLayout * pPrevBL = NULL;
	UT_sint32 i = 0;
	bool bFound = false;

	for(i=0; i< m_vecEntries.getItemCount(); i++)
	{
		pEntry = m_vecEntries.getNthItem(i);
		pPrevBL = pEntry->getBlock();

		if(pPrevBL->getPosition() > posNew)
		{
			bFound = true;
			break;
		}
	}

	UT_sint32 iAllBlocks = 0;
	if(bFound)
	{
		if(i > 0)
		{
			pEntry =  m_vecEntries.getNthItem(i-1);
			pPrevBL =  pEntry->getBlock();
		}
		else
		{
			pEntry = NULL;
			pPrevBL = NULL;
		}
	}

	iAllBlocks = i;

	if(pPrevBL == NULL)
	{
		pPrevBL = static_cast<fl_BlockLayout *>(getFirstLayout());
	}
#if 0
	else if(!m_pLayout->isLayoutFilling())
	{


		PT_DocPosition posStart2 = pPrevBL->getPosition(true);
		PT_DocPosition posEnd2   = posStart2 + static_cast<PT_DocPosition>(pPrevBL->getLength());
		PT_DocPosition posStart  = pBlock->getPosition(true);
		UT_DEBUGMSG(("Prev. affected block is %d long \n",pPrevBL->getLength()));

		if(posEnd2 == posStart)
		{
			fl_BlockLayout * pPrevBL2 = NULL;
			UT_return_if_fail( pEntry && iAllBlocks > 0 );
			UT_UTF8String sDispStyle = pEntry->getDispStyle();
			UT_sint32 iNewLevel = pEntry->getLevel();
			if(i > 1)
			{
				pEntry =  m_vecEntries.getNthItem(i-2);
				pPrevBL2 =  pEntry->getBlock();
			}


			_removeBlockInVec(pPrevBL, true);
			pPrevBL = NULL;

			UT_sint32 iOldLevel = m_iCurrentLevel;
			m_iCurrentLevel = iNewLevel;
			_createAndFillTOCEntry(posStart2, posEnd2, pPrevBL2, sDispStyle.utf8_str(), iAllBlocks - 1);
			m_iCurrentLevel = iOldLevel;


			if(pPrevBL2)
			{
				pPrevBL = static_cast<fl_BlockLayout *>(pPrevBL2->getNext());
			}
			else
			{
				pPrevBL = static_cast<fl_BlockLayout *>(getFirstLayout());
				if(pPrevBL && pPrevBL->getNext())
				{
					pPrevBL = static_cast<fl_BlockLayout *>(pPrevBL->getNext());
				}
			}
		}
	}
#endif
	PT_DocPosition posStart = pBlock->getPosition(true);
	PT_DocPosition posEnd = posStart + static_cast<PT_DocPosition>(pBlock->getLength());

	_createAndFillTOCEntry(posStart, posEnd, pPrevBL, sStyle.utf8_str(), iAllBlocks);


	pBlock->setStyleInTOC(true);
}
