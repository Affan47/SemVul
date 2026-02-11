FetchNameValue( const char *pszName ) const

{
    int iKey = FindName( pszName );

    if( iKey == -1 )
        return NULL;

    CPLAssert( papszList[iKey][strlen(pszName)] == '='
               || papszList[iKey][strlen(pszName)] == ':' );

    return papszList[iKey] + strlen(pszName)+1;
}
