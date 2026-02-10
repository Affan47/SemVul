getClones(UT_GenericVector<XAP_Frame*> *pvClonesCopy, XAP_Frame * pFrame)
{
	UT_ASSERT(pvClonesCopy);
	UT_return_val_if_fail(pFrame,false);
	UT_ASSERT(pFrame->getViewNumber() > 0);


	CloneMap::const_iterator iter = m_hashClones.find(pFrame->getViewKey());
	UT_GenericVector<XAP_Frame*> * pvClones = NULL;
	if (iter != m_hashClones.end()) {
		pvClones = iter->second;
	}
	UT_ASSERT(pvClones);

	return pvClonesCopy->copy(pvClones);
}
