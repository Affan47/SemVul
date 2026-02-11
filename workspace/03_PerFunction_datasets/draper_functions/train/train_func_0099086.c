doclistener_insertFirstBlock(const PX_ChangeRecord_Strux * pcrx,
												  pf_Frag_Strux* sdh,
												  PL_ListenerId lid,
												  void (* pfnBindHandles)(pf_Frag_Strux* sdhNew,
																		  PL_ListenerId lid,
																		  fl_ContainerLayout* sfhNew))
{

	fl_ContainerLayout* sfhNew = this;


	if(pfnBindHandles)
	{
		pfnBindHandles(sdh,lid,sfhNew);
	}
	setNeedsReformat(this);
	updateEnclosingBlockIfNeeded();

	FV_View* pView = getView();
	if (pView && (pView->isActive() || pView->isPreview()))
		pView->_setPoint(pcrx->getPosition());
	else if (pView && ((pView->getPoint() == 0) || pView->getPoint() > pcrx->getPosition()) ) pView->_setPoint(pView->getPoint() + fl_BLOCK_STRUX_OFFSET);
	if(pView)
		pView->updateCarets(pcrx->getPosition(),1);


	_assertRunListIntegrity();

	return true;
}
