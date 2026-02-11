_matchSection(pf_Frag_Strux * pfs, UT_GenericVector<pf_Frag_Strux *> *vecSections)
{
	const char * pszHdrFtr = NULL;
	const char * pszHFID = NULL;
	const char * pszID = NULL;
	UT_sint32 i = 0;
	getAttributeFromSDH(pfs,false,0,"type",&pszHdrFtr);
	if(!pszHdrFtr)
		return false;
	if(!(*pszHdrFtr))
		return false;
	getAttributeFromSDH(pfs,false,0,"id",&pszHFID);
	if(!pszHFID)
		return false;
	if(!(*pszHFID))
		return false;
	for(i= 0; i< vecSections->getItemCount(); i++)
	{
		pf_Frag_Strux * pfsS = vecSections->getNthItem(i);
		getAttributeFromSDH(pfsS,false,0,pszHdrFtr,&pszID);
		if(pszID && *pszID)
		{
			if(strcmp(pszID,pszHFID) == 0)
			{
				return true;
			}
		}
	}
	return false;
}
