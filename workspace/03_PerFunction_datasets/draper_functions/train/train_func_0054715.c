getDocSectionLayout(void) const
{
	fl_DocSectionLayout * pDSL = NULL;
	if(getSectionLayout()->getType() == FL_SECTION_DOC)
	{
		pDSL = static_cast<fl_DocSectionLayout *>( m_pSectionLayout);
		return pDSL;
	}
	else if	(getSectionLayout()->getType() == FL_SECTION_TOC)
	{
		pDSL = static_cast<fl_TOCLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	else if	(getSectionLayout()->getType() == FL_SECTION_FOOTNOTE)
	{
		pDSL = static_cast<fl_FootnoteLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	else if	(getSectionLayout()->getType() == FL_SECTION_ENDNOTE)
	{
		pDSL = static_cast<fl_EndnoteLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	else if	(getSectionLayout()->getType() == FL_SECTION_ANNOTATION)
	{
		pDSL = static_cast<fl_AnnotationLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	else if (getSectionLayout()->getType() == FL_SECTION_HDRFTR)
	{
		pDSL = static_cast<fl_HdrFtrSectionLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	else if (getSectionLayout()->getType() == FL_SECTION_SHADOW)
	{
		pDSL = static_cast<fl_HdrFtrShadow *>( getSectionLayout())->getHdrFtrSectionLayout()->getDocSectionLayout();
		return pDSL;
	}
	else if (getSectionLayout()->getType() == FL_SECTION_CELL)
	{
		pDSL = static_cast<fl_ContainerLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	else if (getSectionLayout()->getType() == FL_SECTION_FRAME)
	{
		pDSL = static_cast<fl_ContainerLayout *>(getSectionLayout())->getDocSectionLayout();
		return pDSL;
	}
	UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
	return NULL;
}
