removeContainer(fp_Container* pContainer,bool bClear)
{
	UT_sint32 iCount = countCons();
	if(iCount == 0)
		return;
	UT_sint32 ndx = findCon(pContainer);
	UT_ASSERT(ndx >= 0);
	if(ndx < 0)
	{
		return;
	}
	if(bClear && (pContainer->getContainerType() == FP_CONTAINER_LINE))
	{
		pContainer->clearScreen();
	}
	xxx_UT_DEBUGMSG(("Removing Container %x from column %x \n",pContainer,this));
	pContainer->setContainer(NULL);
	deleteNthCon(ndx);


}
