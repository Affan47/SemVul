importFromEPSGA( int nCode )

{
    OGRErr  eErr;
    CPLLocaleC  oLocaleForcer;

    bNormInfoSet = FALSE;


    if( GetRoot() != NULL )
    {
        delete poRoot;
        poRoot = NULL;
    }


    if( CSVScanFileByName( CSVFilename( "gcs.csv" ),
                           "COORD_REF_SYS_CODE",
                           "4269", CC_Integer ) == NULL )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Unable to open EPSG support file %s.\n"
                  "Try setting the GDAL_DATA environment variable to point to the\n"
                  "directory containing EPSG csv files.",
                  CSVFilename( "gcs.csv" ) );
        return OGRERR_FAILURE;
    }


    eErr = SetEPSGGeogCS( this, nCode );
    if( eErr == OGRERR_UNSUPPORTED_SRS )
        eErr = SetEPSGProjCS( this, nCode );
    if( eErr == OGRERR_UNSUPPORTED_SRS )
        eErr = SetEPSGVertCS( this, nCode );
    if( eErr == OGRERR_UNSUPPORTED_SRS )
        eErr = SetEPSGCompdCS( this, nCode );
    if( eErr == OGRERR_UNSUPPORTED_SRS )
        eErr = SetEPSGGeocCS( this, nCode );


    if( eErr == OGRERR_UNSUPPORTED_SRS )
    {
        char szCode[32];
        sprintf( szCode, "%d", nCode );
        eErr = importFromDict( "epsg.wkt", szCode );
    }


    if( eErr == OGRERR_UNSUPPORTED_SRS )
    {
        char szWrkDefn[100];
        char *pszNormalized;

        sprintf( szWrkDefn, "+init=epsg:%d", nCode );

        pszNormalized = OCTProj4Normalize( szWrkDefn );

        if( strstr(pszNormalized,"proj=") != NULL )
            eErr = importFromProj4( pszNormalized );

        CPLFree( pszNormalized );
    }


    const char *pszAuthName;

    if( IsProjected() )
        pszAuthName = GetAuthorityName( "PROJCS" );
    else
        pszAuthName = GetAuthorityName( "GEOGCS" );


    if( eErr == OGRERR_NONE && pszAuthName == NULL )
    {
        if( IsProjected() )
            SetAuthority( "PROJCS", "EPSG", nCode );
        else if( IsGeographic() )
            SetAuthority( "GEOGCS", "EPSG", nCode );
    }


    if( eErr == OGRERR_UNSUPPORTED_SRS )
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  "EPSG PCS/GCS code %d not found in EPSG support files.  Is this a valid\nEPSG coordinate system?",
                  nCode );
    }


    if( eErr == OGRERR_NONE )
    {
        eErr = FixupOrdering();
    }

    return eErr;
}
