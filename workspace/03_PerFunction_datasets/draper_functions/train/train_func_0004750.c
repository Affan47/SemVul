PrintSRS( const OGRSpatialReference &oSRS,
                 const char * pszOutputType,
                 int bPretty, int bPrintSep )

{
    if ( ! pszOutputType || EQUAL(pszOutputType,""))
        return CE_None;

    CPLDebug( "gdalsrsinfo", "PrintSRS( oSRS, %s, %d, %d )\n",
              pszOutputType, bPretty, bPrintSep );

    char *pszOutput = NULL;

    if ( EQUAL("proj4", pszOutputType ) ) {
        if ( bPrintSep ) printf( "PROJ.4 : ");
        oSRS.exportToProj4( &pszOutput );
        printf( "\'%s\'\n", pszOutput );
    }

    else if ( EQUAL("wkt", pszOutputType ) ) {
        if ( bPrintSep ) printf("OGC WKT :\n");
        if ( bPretty )
            oSRS.exportToPrettyWkt( &pszOutput, FALSE );
        else
            oSRS.exportToWkt( &pszOutput );
        printf("%s\n",pszOutput);
    }

    else if (  EQUAL("wkt_simple", pszOutputType ) ) {
        if ( bPrintSep ) printf("OGC WKT (simple) :\n");
        oSRS.exportToPrettyWkt( &pszOutput, TRUE );
        printf("%s\n",pszOutput);
    }

    else if ( EQUAL("wkt_noct", pszOutputType ) ) {
        if (  bPrintSep ) printf("OGC WKT (no CT) :\n");
        OGRSpatialReference *poSRS = oSRS.Clone();
        poSRS->StripCTParms( );
        if ( bPretty )
            poSRS->exportToPrettyWkt( &pszOutput, FALSE );
        else
            poSRS->exportToWkt( &pszOutput );
        OGRSpatialReference::DestroySpatialReference( poSRS );
        printf("%s\n",pszOutput);
    }

    else if ( EQUAL("wkt_esri", pszOutputType ) ) {
        if ( bPrintSep ) printf("ESRI WKT :\n");
        OGRSpatialReference *poSRS = oSRS.Clone();
        poSRS->morphToESRI( );
        if ( bPretty )
            poSRS->exportToPrettyWkt( &pszOutput, FALSE );
        else
            poSRS->exportToWkt( &pszOutput );
        OGRSpatialReference::DestroySpatialReference( poSRS );
        printf("%s\n",pszOutput);
    }

    else if ( EQUAL("mapinfo", pszOutputType ) ) {
        if ( bPrintSep ) printf("MAPINFO : ");
        oSRS.exportToMICoordSys( &pszOutput );
        printf("\'%s\'\n",pszOutput);
    }

    else if ( EQUAL("xml", pszOutputType ) ) {
        if ( bPrintSep ) printf("XML :\n");
        oSRS.exportToXML( &pszOutput, NULL );
        printf("%s\n",pszOutput);
    }

    else {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "ERROR - %s output not supported",
                  pszOutputType );
        return CE_Failure;
    }

    CPLFree( pszOutput );

    return CE_None;
}
