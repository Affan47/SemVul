addScheme(XAP_PrefsScheme * pNewScheme)
{
	const gchar * szBuiltinSchemeName = getBuiltinSchemeName();
	const gchar * szThisSchemeName = pNewScheme->getSchemeName();

	if (strcmp(static_cast<const char*>(szThisSchemeName), static_cast<const char*>(szBuiltinSchemeName)) == 0)
	{
		UT_ASSERT(m_builtinScheme == NULL);
		m_builtinScheme = pNewScheme;
	}

	return (m_vecSchemes.addItem(pNewScheme) == 0);
}
