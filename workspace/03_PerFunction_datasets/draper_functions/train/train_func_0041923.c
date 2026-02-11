loadPrefsFile(void)
{
	bool bResult = false;
	const char * szFilename;

	m_parserState.m_parserStatus = true;
	m_parserState.m_bFoundAbiPreferences = false;
	m_parserState.m_bFoundSelect = false;
	m_parserState.m_szSelectedSchemeName = NULL;
	m_parserState.m_bFoundRecent = false;
	m_parserState.m_bFoundGeometry = false;
	m_parserState.m_bFoundFonts = false;
	m_bLoadSystemDefaultFile = false;

	UT_XML parser;

	szFilename = getPrefsPathname();
	if (!szFilename)
	{
		UT_DEBUGMSG(("could not get pathname for preferences file.\n"));
		goto Cleanup;
	}

	parser.setListener (this);
	if ((parser.parse (szFilename) != UT_OK) || (!m_parserState.m_parserStatus))
	{
		UT_DEBUGMSG(("Problem reading (Preferences) document\n"));
		goto Cleanup;
	}


	if (!m_parserState.m_bFoundAbiPreferences)
	{
		UT_DEBUGMSG(("Did not find <AbiPreferences...>\n"));
		goto Cleanup;
	}
	if (!m_parserState.m_bFoundSelect)
	{
		UT_DEBUGMSG(("Did not find <Select...>\n"));
		goto Cleanup;
	}
	if (!m_parserState.m_bFoundRecent)
	{
		UT_DEBUGMSG(("Did not find <Recent...>\n"));

	}
	if (!m_parserState.m_bFoundGeometry)
	{
		UT_DEBUGMSG(("Did not find <Geometry...>\n"));

	}

	UT_ASSERT(m_parserState.m_szSelectedSchemeName);
	if (!setCurrentScheme(m_parserState.m_szSelectedSchemeName))
	{
		UT_DEBUGMSG(("Selected scheme [%s] not found in preferences file.\n",
					m_parserState.m_szSelectedSchemeName));
		goto Cleanup;
	}

	bResult = true;
Cleanup:
	FREEP(m_parserState.m_szSelectedSchemeName);

	return bResult;
}
