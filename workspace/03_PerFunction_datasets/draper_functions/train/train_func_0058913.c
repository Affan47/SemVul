getNthFmtHandle(pf_Frag_Strux* sdh, UT_uint32 n)
{
	const pf_Frag_Strux * pfs = static_cast<const pf_Frag_Strux *>(sdh);
	UT_uint32 nListen = m_vecListeners.getItemCount();
	if(n >= nListen)
		return NULL;
	PL_ListenerId lid = static_cast<PL_ListenerId>(n);
	fl_ContainerLayout* sfh = pfs->getFmtHandle(lid);
	return sfh;
}
