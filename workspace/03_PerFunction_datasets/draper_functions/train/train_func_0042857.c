getEditableBounds(bool isEnd, PT_DocPosition &posEOD, bool bOveride) const
{
	bool res=true;
	fl_SectionLayout * pSL = NULL;
	fl_BlockLayout * pBL = NULL;
	if(!isEnd && (!m_bEditHdrFtr || bOveride))
	{
		res = m_pDoc->getBounds(isEnd,posEOD);
		return res;
	}
	if(!m_bEditHdrFtr || bOveride)
	{
		pSL = static_cast<fl_SectionLayout *>(m_pLayout->getLastSection());

		if(!pSL)
		{
			UT_ASSERT(UT_SHOULD_NOT_HAPPEN);
			res = m_pDoc->getBounds(isEnd,posEOD);
			return res;
		}


		while(pSL->getNext() != NULL && (pSL->getContainerType() != FL_CONTAINER_HDRFTR))
		{
			pSL = static_cast<fl_SectionLayout *>(pSL->getNext());
		}
		if(pSL->getContainerType() != FL_CONTAINER_HDRFTR)
		{
			res = m_pDoc->getBounds(isEnd,posEOD);
			return res;
		}


		fl_ContainerLayout * pFirstCL = pSL->getFirstLayout();
		if(pFirstCL == NULL)
		{
			res = m_pDoc->getBounds(isEnd,posEOD);
			return res;
		}

		PT_DocPosition posFirst = pFirstCL->getPosition(true) - 1;
		PT_DocPosition posNext;
		while((pSL->getNext() != NULL) && (pSL->getNextBlockInDocument() != NULL))
		{
			pSL = static_cast<fl_SectionLayout *>(pSL->getNext());
			pFirstCL = pSL->getFirstLayout();


			if (pFirstCL)
			{
				posNext = pFirstCL->getPosition(true) - 1;
				if(posNext < posFirst)
					posFirst = posNext;
			}
		}
		posEOD = posFirst;
		return res;
	}


	if(!isEnd)
	{
		UT_return_val_if_fail(m_pEditShadow->getFirstLayout(), false);
		posEOD = m_pEditShadow->getFirstLayout()->getPosition();
		return true;
	}
	pBL = static_cast<fl_BlockLayout *>(m_pEditShadow->getLastLayout());
	UT_return_val_if_fail(pBL, false);
	posEOD = pBL->getPosition(false);
	fp_Run * pRun = pBL->getFirstRun();
	while( pRun && pRun->getNextRun() != NULL)
	{
		pRun = pRun->getNextRun();
	}
	if(pRun)
	{
		posEOD += pRun->getBlockOffset();
	}
	return true;
}
