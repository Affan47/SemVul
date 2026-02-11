getStruxFromPosition(PL_ListenerId listenerId,
											PT_DocPosition docPos,
											fl_ContainerLayout* * psfh) const
{


	pf_Frag_Strux * pfs = NULL;
	if (!_getStruxFromPosition(docPos,&pfs))
		return false;

	*psfh = pfs->getFmtHandle(listenerId);
	return true;
}
