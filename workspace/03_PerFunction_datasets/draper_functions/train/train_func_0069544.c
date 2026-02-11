CPLURLGetValue(const char* pszURL, const char* pszKey)
{
    CPLString osKey(pszKey);
    osKey += "=";
    size_t nKeyPos = CPLString(pszURL).ifind(osKey);
    if (nKeyPos != std::string::npos && nKeyPos > 0 &&
        (pszURL[nKeyPos-1] == '?' || pszURL[nKeyPos-1] == '&'))
    {
        CPLString osValue(pszURL + nKeyPos + strlen(osKey));
        const char* pszValue = osValue.c_str();
        const char* pszSep = strchr(pszValue, '&');
        if (pszSep)
        {
            osValue.resize(pszSep - pszValue);
        }
        return osValue;
    }
    return "";
}
