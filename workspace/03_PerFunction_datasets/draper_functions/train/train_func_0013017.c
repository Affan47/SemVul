doclistener_deleteStrux(const PX_ChangeRecord_Strux * pcrx)
{
	UT_ASSERT(pcrx->getType()==PX_ChangeRecord::PXT_DeleteStrux);
	UT_ASSERT(pcrx->getStruxType()==PTX_Section);
	UT_DEBUGMSG(("Doing Section delete \n"));
	fl_DocSectionLayout* pPrevSL = getPrevDocSection();
	UT_DEBUGMSG(("Deleting DocSec %p Prev DocSec %p \n",this,pPrevSL));
	if (!pPrevSL)
	{

		UT_DEBUGMSG(("no prior SectionLayout"));
		return false;
	}


	pPrevSL->collapse();


	collapse();

	DELETEP(m_pHeaderSL);
	DELETEP(m_pHeaderEvenSL);
	DELETEP(m_pHeaderFirstSL);
	DELETEP(m_pHeaderLastSL);
	DELETEP(m_pFooterSL);
	DELETEP(m_pFooterEvenSL);
	DELETEP(m_pFooterFirstSL);
	DELETEP(m_pFooterLastSL);


	fl_DocSectionLayout * pDSL = getNextDocSection();
	while(pDSL != NULL)
	{
		pDSL->collapse();
		pDSL = pDSL->getNextDocSection();
	}


	if(getFirstLayout())
	{
		fl_ContainerLayout * pBCur = getFirstLayout();
		fl_ContainerLayout * pBPrev = pPrevSL->getLastLayout();
		UT_ASSERT(pBCur && pBPrev);

		pBCur->setPrev(pBPrev);
		pBPrev->setNext(pBCur);
		while(pBCur != NULL)
		{
			xxx_UT_DEBUGMSG(("updating block %x \n",pBCur));
			pBCur->setContainingLayout(pPrevSL);
			if(pBCur->getContainerType() == FL_CONTAINER_BLOCK)
			{
				static_cast<fl_BlockLayout *>(pBCur)->
					setSectionLayout(pPrevSL);
			}
			if(pBCur->getContainerType() == FL_CONTAINER_FOOTNOTE)
			{
				static_cast<fl_FootnoteLayout *>(pBCur)->
					setDocSectionLayout(pPrevSL);
			}
			if(pBCur->getContainerType() == FL_CONTAINER_ANNOTATION)
			{
				static_cast<fl_AnnotationLayout *>(pBCur)->
					setDocSectionLayout(pPrevSL);
			}
			if(pBCur->getContainerType() == FL_CONTAINER_ENDNOTE)
			{
				static_cast<fl_EndnoteLayout *>(pBCur)->
					setDocSectionLayout(pPrevSL);
			}

			pPrevSL->setLastLayout(pBCur);
			pBCur = pBCur->getNext();
		}
	}
	setFirstLayout(NULL);
	setLastLayout(NULL);


    pDSL = getNextDocSection();
	m_pLayout->removeSection(this);
	pPrevSL->format();

	FV_View* pView = m_pLayout->getView();
	if (pView)
  	{
  		pView->_setPoint(pcrx->getPosition());
  	}


	while(pDSL != NULL)
	{
		pDSL->updateDocSection();
		pDSL = pDSL->getNextDocSection();
	}
	delete this;

	return true;
}
