_lookupProperties(const PP_AttrProp* pSectionAP)
{
	UT_return_if_fail(pSectionAP);


	const gchar *pszFootnotePID = NULL;
	if(!pSectionAP->getAttribute("footnote-id",pszFootnotePID))
	{
		m_iFootnotePID = 0;
	}
	else
	{
		m_iFootnotePID = atoi(pszFootnotePID);
	}
}
