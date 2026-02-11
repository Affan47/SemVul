GTIFGetEllipsoidInfo( int nEllipseCode, char ** ppszName,
                          double * pdfSemiMajor, double * pdfSemiMinor )

{
    char	szSearchKey[24];
    double	dfSemiMajor=0.0, dfToMeters = 1.0;
    int		nUOMLength;
    const char* pszFilename;


    double     dfInvFlattening=0.0, dfSemiMinor=0.0;
    const char *pszName = NULL;

    if( nEllipseCode == Ellipse_Clarke_1866 )
    {
        pszName = "Clarke 1866";
        dfSemiMajor = 6378206.4;
        dfSemiMinor = 6356583.8;
        dfInvFlattening = 0.0;
    }
    else if( nEllipseCode == Ellipse_GRS_1980 )
    {
        pszName = "GRS 1980";
        dfSemiMajor = 6378137.0;
        dfSemiMinor = 0.0;
        dfInvFlattening = 298.257222101;
    }
    else if( nEllipseCode == Ellipse_WGS_84 )
    {
        pszName = "WGS 84";
        dfSemiMajor = 6378137.0;
        dfSemiMinor = 0.0;
        dfInvFlattening = 298.257223563;
    }
    else if( nEllipseCode == 7043 )
    {
        pszName = "WGS 72";
        dfSemiMajor = 6378135.0;
        dfSemiMinor = 0.0;
        dfInvFlattening = 298.26;
    }

    if (pszName != NULL)
    {
        if( dfSemiMinor == 0.0 )
            dfSemiMinor = dfSemiMajor * (1 - 1.0/dfInvFlattening);

        if( pdfSemiMinor != NULL )
            *pdfSemiMinor = dfSemiMinor;
        if( pdfSemiMajor != NULL )
            *pdfSemiMajor = dfSemiMajor;
        if( ppszName != NULL )
            *ppszName = CPLStrdup( pszName );

        return TRUE;
    }


    sprintf( szSearchKey, "%d", nEllipseCode );
    pszFilename = CSVFilename("ellipsoid.csv" );

    dfSemiMajor =
        GTIFAtof(CSVGetField( pszFilename,
                          "ELLIPSOID_CODE", szSearchKey, CC_Integer,
                          "SEMI_MAJOR_AXIS" ) );

    if( dfSemiMajor == 0.0 )
    {
        return FALSE;
    }


    nUOMLength = atoi(CSVGetField( pszFilename,
                                   "ELLIPSOID_CODE", szSearchKey, CC_Integer,
                                   "UOM_CODE" ));
    GTIFGetUOMLengthInfo( nUOMLength, NULL, &dfToMeters );

    dfSemiMajor *= dfToMeters;

    if( pdfSemiMajor != NULL )
        *pdfSemiMajor = dfSemiMajor;


    if( pdfSemiMinor != NULL )
    {
        *pdfSemiMinor =
            GTIFAtof(CSVGetField( pszFilename,
                              "ELLIPSOID_CODE", szSearchKey, CC_Integer,
                              "SEMI_MINOR_AXIS" )) * dfToMeters;

        if( *pdfSemiMinor == 0.0 )
        {
            double	dfInvFlattening;

            dfInvFlattening =
                GTIFAtof(CSVGetField( pszFilename,
                                  "ELLIPSOID_CODE", szSearchKey, CC_Integer,
                                  "INV_FLATTENING" ));
            *pdfSemiMinor = dfSemiMajor * (1 - 1.0/dfInvFlattening);
        }
    }


    if( ppszName != NULL )
        *ppszName =
            CPLStrdup(CSVGetField( pszFilename,
                                   "ELLIPSOID_CODE", szSearchKey, CC_Integer,
                                   "ELLIPSOID_NAME" ));

    return( TRUE );
}
