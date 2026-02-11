OGRGeocodeGetParameter(char** papszOptions, const char* pszKey,
                                   const char* pszDefaultValue)
{
    const char* pszRet = CSLFetchNameValue(papszOptions, pszKey);
    if( pszRet != NULL )
        return pszRet;

    return CPLGetConfigOption(CPLSPrintf("OGR_GEOCODE_%s", pszKey),
                              pszDefaultValue);
}
