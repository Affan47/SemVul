getPrefsValueDirectory(bool bAppSpecific,
										const gchar * szKey, const gchar ** pszValue) const
{
    if (!m_prefs)
		return false;

    const gchar * psz = NULL;
    if (!m_prefs->getPrefsValue(szKey,&psz))
		return false;

    if (*psz == '/')
    {
		*pszValue = psz;
		return true;
    }

    const gchar * dir = ((bAppSpecific) ? getAbiSuiteAppDir() : getAbiSuiteLibDir());

    static gchar buf[1024];
    UT_ASSERT((strlen(dir) + strlen(psz) + 2) < sizeof(buf));

    sprintf(buf,"%s/%s",dir,psz);
    *pszValue = buf;
    return true;
}
