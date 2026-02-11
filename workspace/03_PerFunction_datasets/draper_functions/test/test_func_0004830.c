collapse(void)
{
	UT_DEBUGMSG(("Collapsing  Endnote %p \n",this));
	_localCollapse();
	fp_EndnoteContainer *pFC = static_cast<fp_EndnoteContainer *>(getFirstContainer());
	while(pFC)
	{
		fp_EndnoteContainer *pNext = static_cast<fp_EndnoteContainer *>(pFC->getLocalNext());
		m_pLayout->removeEndnoteContainer(pFC);
		fp_EndnoteContainer * pPrev = static_cast<fp_EndnoteContainer *>(pFC->getPrev());
		if(pPrev)
		{
			pPrev->setNext(pFC->getNext());
		}
		if(pFC->getNext())
		{
			pFC->getNext()->setPrev(pPrev);
		}
		delete pFC;
		pFC = pNext;
	}
	setFirstContainer(NULL);
	setLastContainer(NULL);
	m_bIsOnPage = false;
}
