FindFile( const char *pszTarget,
                                 const char *pszDirectory,
                                 int bReportErr,
                                 VSILFILE **pfp )

{
    const char *pszFilename;

    if( pszDirectory == NULL )
    {
        pszFilename = CPLFindFile( "s57", pszTarget );
        if( pszFilename == NULL )
            pszFilename = pszTarget;
    }
    else
    {
        pszFilename = CPLFormFilename( pszDirectory, pszTarget, NULL );
    }

    *pfp = VSIFOpenL( pszFilename, "rb" );

#ifdef S57_BUILTIN_CLASSES
    if( *pfp == NULL )
    {
        if( EQUAL(pszTarget, "s57objectclasses.csv") )
            papszNextLine = gpapszS57Classes;
        else
            papszNextLine = gpapszS57attributes;
    }
#else
    if( *pfp == NULL )
    {
        if( bReportErr )
            CPLError( CE_Failure, CPLE_OpenFailed,
                      "Failed to open %s.\n",
                      pszFilename );
        return FALSE;
    }
#endif

    return TRUE;
}
