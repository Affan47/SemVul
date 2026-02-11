_createEndnoteContainer(void)
{
	lookupProperties();
	fp_EndnoteContainer * pEndnoteContainer = new fp_EndnoteContainer(static_cast<fl_SectionLayout *>(this));
	setFirstContainer(pEndnoteContainer);
	setLastContainer(pEndnoteContainer);
	fl_DocSectionLayout * pDSL = m_pLayout->getDocSecForEndnote(pEndnoteContainer);
	UT_sint32 iWidth = m_pLayout->getLastPage()->getWidth();
	iWidth = iWidth - pDSL->getLeftMargin() - pDSL->getRightMargin();
	pEndnoteContainer->setWidth(iWidth);
	m_bNeedsReformat = true;
	m_bNeedsFormat = true;
}
