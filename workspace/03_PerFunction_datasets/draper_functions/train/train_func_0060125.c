bl_doclistener_insertCell(fl_ContainerLayout* pCell,
											  const PX_ChangeRecord_Strux * pcrx,
											  pf_Frag_Strux* sdh,
											  PL_ListenerId lid,
											  void (* pfnBindHandles)(pf_Frag_Strux* sdhNew,
																	  PL_ListenerId lid,
																	  fl_ContainerLayout* sfhNew))
{
	fl_ContainerLayout * pNewCL = NULL;
	fl_TableLayout * pTL = static_cast<fl_TableLayout *>(myContainingLayout());
	pNewCL = pTL->insert(sdh,pCell,pcrx->getIndexAP(), FL_CONTAINER_CELL);


	if(	pfnBindHandles)
	{
		fl_ContainerLayout* sfhNew = pNewCL;
		pfnBindHandles(sdh,lid,sfhNew);
	}
	fl_CellLayout * pCL = static_cast<fl_CellLayout *>(pNewCL);
	pTL->attachCell(pCL);


	FV_View* pView = m_pLayout->getView();
	if (pView && (pView->isActive() || pView->isPreview()))
	{
		pView->setPoint(pcrx->getPosition() +  fl_BLOCK_STRUX_OFFSET);
	}
	else if(pView && pView->getPoint() > pcrx->getPosition())
	{
		pView->setPoint(pView->getPoint() +  fl_BLOCK_STRUX_OFFSET);
	}
	if(pView)
		pView->updateCarets(pcrx->getPosition(),1);
	return true;
}
