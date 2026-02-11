createCellContainer(void)
{
	lookupProperties();
	if(isHidden() >= FP_HIDDEN_FOLDED)
	{
		xxx_UT_DEBUGMSG(("Don't format coz I'm hidden! \n"));
		return;
	}

	fp_CellContainer * pCellContainer = new fp_CellContainer(static_cast<fl_SectionLayout *>(this));
	setFirstContainer(pCellContainer);
	setLastContainer(pCellContainer);
	fl_ContainerLayout * pCL = myContainingLayout();
	while(pCL!= NULL && ((pCL->getContainerType() != FL_CONTAINER_DOCSECTION) && (pCL->getContainerType() != FL_CONTAINER_HDRFTR)))
	{
		pCL = pCL->myContainingLayout();
	}
	fl_DocSectionLayout * pDSL = NULL;
	if(pCL->getContainerType() == FL_CONTAINER_HDRFTR)
	{
		pDSL = static_cast<fl_HdrFtrSectionLayout *>(pCL)->getDocSectionLayout();
	}
	else
	{
		pDSL = static_cast<fl_DocSectionLayout *>(pCL);
	}
	UT_ASSERT(pDSL != NULL);
	UT_sint32 iWidth = pDSL->getWidth();
	pCellContainer->setWidth(iWidth);


	const PP_AttrProp* pSectionAP = NULL;


	getAP(pSectionAP);

	const gchar * pszDataID = NULL;
	pSectionAP->getAttribute(PT_STRUX_IMAGE_DATAID, (const gchar *&)pszDataID);
	DELETEP(m_pGraphicImage);
	DELETEP(m_pImageImage);
	if(pszDataID && *pszDataID)
	{
		UT_DEBUGMSG(("!!!Found image of file %s \n",pszDataID));
		UT_DEBUGMSG(("LeftAttach %d \n",m_iLeftAttach));
		m_pGraphicImage = FG_Graphic::createFromStrux(this);
	}
	setCellContainerProperties(pCellContainer);

}
