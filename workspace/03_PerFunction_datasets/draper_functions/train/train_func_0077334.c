VBreakAt(UT_sint32 vpos)
{
	UT_sint32 iBreakTick = getBreakTick();
	iBreakTick++;
	setBreakTick(iBreakTick);
	xxx_UT_DEBUGMSG(("iBreakTick is %d \n",getBreakTick()));
	if(!containsNestedTables())
	{
		return NULL;
	}
	UT_sint32 count = countCons();
	UT_DEBUGMSG(("vBREAK cell at  %d \n",vpos));
	UT_sint32 i = 0;
	fp_Container * pCon;
	fp_TableContainer * pBroke = NULL;
	UT_sint32 iY = 0;
	for(i=0; (i < count) || (iY <= vpos); i++)
	{
		pCon = static_cast<fp_Container *>(getNthCon(i));
		xxx_UT_DEBUGMSG(("Looking Container iY  %d height %d \n",iY,pCon->getHeight()));
		if(iY <= vpos && iY + pCon->getHeight() > vpos)
		{


			if(pCon->isVBreakable())
			{
				if(pCon->getContainerType() == FP_CONTAINER_TABLE)
				{
					UT_DEBUGMSG(("Want to break nested table at %d \n",vpos));
					fp_TableContainer * pTab = static_cast<fp_TableContainer *>(pCon);
					if(!pTab->isThisBroken())
					{
						if(pTab->getY() < -999999)
						{
							pTab->setY(iY);
						}
						if(pTab->getFirstBrokenTable())
						{
							pCon = static_cast<fp_Container *>(pTab->getFirstBrokenTable());
						}
						else
						{
							pCon = static_cast<fp_Container *>(pTab->VBreakAt(0));
							fp_TableContainer * pBTab = static_cast<fp_TableContainer *>(pCon);
							pBTab->setY(iY);
							UT_DEBUGMSG(("Break Nested table Con %p at 0 y %d height %d \n",pCon,pCon->getY(),pCon->getHeight()));
							UT_DEBUGMSG(("Break Nested table Table %p at 0 y %d height %d \n",pBTab,pBTab->getY(),pBTab->getHeight()));
						}
					}
				}
				if(vpos > 0)
				{


					fp_TableContainer * pPrevTab = static_cast<fp_TableContainer *>(pCon);
					fp_TableContainer * pMaster = pPrevTab->getMasterTable();
					pBroke = static_cast<fp_TableContainer *>(pPrevTab->VBreakAt(vpos - pMaster->getY() - pPrevTab->getYBreak()));
					if (pBroke)
					{
						pBroke->setY(vpos);
						static_cast<fp_TableContainer *>(pBroke)->setY(pBroke->getY());
						UT_DEBUGMSG(("Made broken nested Table %p Y %d height %d \n",pBroke,pBroke->getY(),pBroke->getHeight()));
						UT_ASSERT(pBroke->getContainer() == this);
					}
					break;
				}
			}
		}
		iY += pCon->getHeight();
		iY += pCon->getMarginAfter();
	}
	return static_cast<fp_ContainerObject *>(pBroke);
}
