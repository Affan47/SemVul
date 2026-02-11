setCurrentScheme(const gchar * szSchemeName)
{


	XAP_PrefsScheme * p = getScheme(szSchemeName);
	if (!p)
		return false;

	UT_DEBUGMSG(("Preferences::setCurrentScheme [%s].\n",szSchemeName));

	m_currentScheme = p;
	return true;
}
