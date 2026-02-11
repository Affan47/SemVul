bl_doclistener_insertCell(fl_ContainerLayout* pCell,
											  const PX_ChangeRecord_Strux * pcrx,
											  pf_Frag_Strux* sdh,
											  PL_ListenerId lid,
											  fl_TableLayout * pTL)
{
	UT_uint32 iCount = m_vecPages.getItemCount();
	fl_ContainerLayout * pShadowBL = NULL;
	UT_DEBUGMSG(("fl_HdrFtrSectionLayout: insertCells into shadows \n"));
	m_pDoc->setDontChangeInsPoint();
	bool bResult = true;
	for (UT_uint32 i=0; i<iCount; i++)
	{
		_PageHdrFtrShadowPair* pPair = m_vecPages.getNthItem(i);


		pShadowBL = pPair->getShadow()->findMatchingContainer(pTL);
		fl_ContainerLayout * pPrevCell = NULL;
		if(pCell)
		{
			pPrevCell = pPair->getShadow()->findMatchingContainer(pCell);
		}
		UT_DEBUGMSG(("fl_HdrFtrSectionLayout: insertCell into Table shadow \n"));
		if(pShadowBL)
		{
			bResult = static_cast<fl_TableLayout *>(pShadowBL)->bl_doclistener_insertCell(pPrevCell,pcrx,sdh,lid,NULL)
				&& bResult;
		}
	}
	m_pDoc->allowChangeInsPoint();
	return true;

}
