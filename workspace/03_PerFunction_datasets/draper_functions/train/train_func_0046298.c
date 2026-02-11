SetAttributeFilter( const char *pszQuery )

{
    if( (pszQuery == NULL && this->pszQuery == NULL)
        || (pszQuery != NULL && this->pszQuery != NULL
            && EQUAL(pszQuery,this->pszQuery)) )
        return OGRERR_NONE;

    CPLFree( this->pszQuery );
    this->pszQuery = (pszQuery) ? CPLStrdup( pszQuery ) : NULL;

    ClearStatement();

    return OGRERR_NONE;
}
