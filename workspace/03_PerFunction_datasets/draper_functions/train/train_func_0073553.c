Read( const char * pszFilename )

{
    DDFModule   oCATDFile;
    DDFRecord   *poRecord;


    if( !oCATDFile.Open( pszFilename ) )
        return FALSE;

    CPLErrorReset();


    if( oCATDFile.FindFieldDefn( "CATD" ) == NULL )
        return FALSE;


    int         i;

    pszPrefixPath = CPLStrdup( pszFilename );
    for( i = strlen(pszPrefixPath)-1; i > 0; i-- )
    {
        if( pszPrefixPath[i] == '\\' || pszPrefixPath[i] == '/' )
        {
            pszPrefixPath[i] = '\0';
            break;
        }
    }

    if( i <= 0 )
    {
        strcpy( pszPrefixPath, "." );
    }


    while( (poRecord = oCATDFile.ReadRecord()) != NULL )
    {


        if( poRecord->GetStringSubfield( "CATD", 0, "MODN", 0 ) == NULL )
            continue;


        SDTS_CATDEntry  *poEntry = new SDTS_CATDEntry;

        poEntry->pszModule =
            CPLStrdup(poRecord->GetStringSubfield( "CATD", 0, "NAME", 0 ));
        poEntry->pszFile =
            CPLStrdup(poRecord->GetStringSubfield( "CATD", 0, "FILE", 0 ));
        poEntry->pszExternalFlag =
            CPLStrdup(poRecord->GetStringSubfield( "CATD", 0, "EXTR", 0 ));
        poEntry->pszType =
            CPLStrdup(poRecord->GetStringSubfield( "CATD", 0, "TYPE", 0 ));


        poEntry->pszFullPath =
            CPLStrdup(CPLFormCIFilename( pszPrefixPath, poEntry->pszFile,
                                         NULL ));


        papoEntries = (SDTS_CATDEntry **)
            CPLRealloc(papoEntries, sizeof(void*) * ++nEntries );
        papoEntries[nEntries-1] = poEntry;
    }

    return nEntries > 0;
}
