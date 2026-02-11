GetColData( const char *pszColName,
                                          const char *pszDefault )

{
    int iCol = GetColId( pszColName );

    if( iCol == -1 )
        return pszDefault;
    else
        return GetColData( iCol, pszDefault );
}
