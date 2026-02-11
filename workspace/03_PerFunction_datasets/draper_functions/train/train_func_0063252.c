CSVGetNextLine( const char *pszFilename )

{
    CSVTable *psTable;


    CPLAssert( pszFilename != NULL );

    psTable = CSVAccess( pszFilename );
    if( psTable == NULL )
        return NULL;


    psTable->bNonUniqueKey = TRUE;


    if( psTable->iLastLine+1 >= psTable->nLineCount )
        return NULL;

    psTable->iLastLine++;
    CSLDestroy( psTable->papszRecFields );
    psTable->papszRecFields =
        CSVSplitLine( psTable->papszLines[psTable->iLastLine], ',' );

    return psTable->papszRecFields;
}
