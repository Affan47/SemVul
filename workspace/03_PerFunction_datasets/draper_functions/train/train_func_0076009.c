bl_doclistener_populateObject(fl_ContainerLayout* pBL, PT_BlockOffset blockOffset, const PX_ChangeRecord_Object * pcro)
{


  	bool bResult = true;
	fl_ContainerLayout * pShadowBL = NULL;
	UT_uint32 iCount = m_vecPages.getItemCount();
	m_pDoc->setDontChangeInsPoint();
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = m_vecPages.getNthItem(i);

		pShadowBL = pPair->getShadow()->findMatchingContainer(pBL);
		if(pShadowBL)
		{
			bResult = static_cast<fl_BlockLayout *>(pShadowBL)->doclistener_populateObject(blockOffset,pcro)
				&& bResult;
		}
		else
		{
			bResult = false;
		}
	}
	m_pDoc->allowChangeInsPoint();
	pBL = findMatchingContainer(pBL);
	if(pBL)
	{
		bResult = static_cast<fl_BlockLayout *>(pBL)->doclistener_populateObject(blockOffset,pcro)
			&& bResult;
	}
	else
	{
		bResult = false;
	}
	return bResult;
}
