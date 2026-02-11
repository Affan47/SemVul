s_BindHandles(pf_Frag_Strux* sdhNew,
						  PL_ListenerId lid,
						  fl_ContainerLayout* sfhNew)
{
	UT_return_if_fail (sdhNew);
	UT_return_if_fail (sfhNew);

	pf_Frag_Strux * pfsNew = sdhNew;
	UT_DEBUGMSG(("Set Format handle number %d of strux %p to format %p \n",lid,pfsNew,sfhNew));
	pfsNew->setFmtHandle(lid,sfhNew);
}
