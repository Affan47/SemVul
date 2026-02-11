GetNextStyle()
{
    const char *pszDash = NULL;
    const char *pszOutput = NULL;

    while( iNextStyle < CSLCount(m_papszStyleTable) )
    {

        if ( NULL == (pszOutput = CSLGetField(m_papszStyleTable,iNextStyle++)))
            continue;

        pszDash = strstr(pszOutput,":");

        int nColon;

        osLastRequestedStyleName = pszOutput;
        nColon = osLastRequestedStyleName.find( ':' );
        if( nColon != -1 )
            osLastRequestedStyleName =
                osLastRequestedStyleName.substr(0,nColon);

        if (pszDash)
            return pszDash + 1;
    }
    return NULL;
}
