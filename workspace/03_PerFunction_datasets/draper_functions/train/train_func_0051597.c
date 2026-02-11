RECGetFieldCount( FILE * fp )

{
    const char *pszLine = CPLReadLine( fp );
    if( pszLine == NULL )
        return -1;
    if( atoi(pszLine) < 1 )
        return -1;

    nNextRecLine = 1;

    return atoi(pszLine);
}
