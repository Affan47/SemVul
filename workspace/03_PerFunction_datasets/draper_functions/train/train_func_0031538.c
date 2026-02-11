OGRSQLiteEscapeName(const char* pszName)
{
    CPLString osRet;
    while( *pszName != '\0' )
    {
        if( *pszName == '"' )
            osRet += "\"\"";
        else
            osRet += *pszName;
        pszName ++;
    }
    return osRet;
}
