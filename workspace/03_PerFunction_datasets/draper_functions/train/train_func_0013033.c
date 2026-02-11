setNeedsSectionBreak(bool bSet, fp_Page * pPage)
{
	m_bNeedsSectionBreak = bSet;
	fp_Page * pOldP = m_ColumnBreaker.getStartPage();
	UT_sint32 iOldP = 999999999;
	if(pPage == NULL)
	{
	  UT_DEBUGMSG(("SectionBreak from start \n"));
		m_ColumnBreaker.setStartPage(pPage);
		return;
	}
	if(pPage->getOwningSection() != this)
	{
		m_ColumnBreaker.setStartPage(NULL);
		return;
	}
	if(pOldP)
	{
		iOldP = getDocLayout()->findPage(pOldP);
	}
	UT_sint32 iNewP = getDocLayout()->findPage(pPage);
	xxx_UT_DEBUGMSG(("setNeedsSectionBreak: new Page %d OldPage %d \n",iNewP,iOldP));
	if( (iNewP > -1) && (iNewP < iOldP))
	{
		xxx_UT_DEBUGMSG(("setNeedsSectionBreak: Rebuild from Page %x \n",pPage));
		m_ColumnBreaker.setStartPage(pPage);
	}
}
