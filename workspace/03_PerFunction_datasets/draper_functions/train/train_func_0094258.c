NCDFTokenizeArray( const char *pszValue )
{
    char **papszValues = NULL;
    char *pszTemp = NULL;
    int nLen = 0;

    if ( pszValue==NULL || EQUAL( pszValue, "" ) )
        return NULL;

    nLen = strlen(pszValue);

    if ( ( pszValue[0] == '{' ) && ( pszValue[nLen-1] == '}' ) ) {
        pszTemp = (char *) CPLCalloc(nLen-2,sizeof(char*));
        strncpy( pszTemp, pszValue+1, nLen-2);
        pszTemp[nLen-2] = '\0';
        papszValues = CSLTokenizeString2( pszTemp, ",", CSLT_ALLOWEMPTYTOKENS );
        CPLFree( pszTemp);
    }
    else {
        papszValues = (char**) CPLCalloc(2,sizeof(char*));
        papszValues[0] = CPLStrdup( pszValue );
        papszValues[1] = NULL;
    }

    return papszValues;
}
