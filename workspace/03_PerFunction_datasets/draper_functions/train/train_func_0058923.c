printErrorPage(
	const char *	pszErrStr,
	const char *	pszErrStr2,
	FLMBOOL			bStdHeader)
{
	printDocStart( "Error", TRUE, bStdHeader);

	fnPrintf( m_pHRequest, "<center><h2>\n");
	fnPrintf( m_pHRequest, "%s\n", pszErrStr);
	if (pszErrStr2 && *pszErrStr2)
	{
		fnPrintf( m_pHRequest, "<BR>%s\n", pszErrStr2);
	}

	fnPrintf( m_pHRequest, "</h2></center>\n");

	printDocEnd();
}
