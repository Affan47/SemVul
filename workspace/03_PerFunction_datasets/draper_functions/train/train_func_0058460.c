format(void)
{
	UT_DEBUGMSG(("SEVIOR: Formatting Endnote first container is %p \n",getFirstContainer()));
	if(getFirstContainer() == NULL)
	{
		getNewContainer();
	}
	if(!m_bIsOnPage)
	{
		_insertEndnoteContainer(getFirstContainer());
	}
	fl_ContainerLayout*	pBL = getFirstLayout();
	while (pBL)
	{
		pBL->format();
		UT_sint32 count = 0;
		while(pBL->getLastContainer() == NULL || pBL->getFirstContainer()==NULL)
		{
			UT_DEBUGMSG(("Error formatting a block try again \n"));
			count = count + 1;
			pBL->format();
			if(count > 3)
			{
				UT_DEBUGMSG(("Give up trying to format. Hope for the best :-( \n"));
				break;
			}
		}
		pBL = pBL->getNext();
	}
	static_cast<fp_EndnoteContainer *>(getFirstContainer())->layout();
	m_bNeedsFormat = false;
	m_bNeedsReformat = false;
	bool bOnPage = (getFirstContainer()->getPage() != NULL);
	FV_View * pView = NULL;
	if(m_pLayout)
		pView = m_pLayout->getView();
	if(bOnPage && pView && !pView->isLayoutFilling())
	{
	       getDocSectionLayout()->setNeedsSectionBreak(true,NULL);
	}
	UT_ASSERT(getFirstContainer()->getPage());
}
