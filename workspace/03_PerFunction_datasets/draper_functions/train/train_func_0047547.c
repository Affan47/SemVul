GDALInfoReportCorner( GDALDatasetH hDataset,
                      OGRCoordinateTransformationH hTransform,
                      const char * corner_name,
                      double x, double y )

{
    double	dfGeoX, dfGeoY;
    double	adfGeoTransform[6];

    printf( "%-11s ", corner_name );


    if( GDALGetGeoTransform( hDataset, adfGeoTransform ) == CE_None )
    {
        dfGeoX = adfGeoTransform[0] + adfGeoTransform[1] * x
            + adfGeoTransform[2] * y;
        dfGeoY = adfGeoTransform[3] + adfGeoTransform[4] * x
            + adfGeoTransform[5] * y;
    }

    else
    {
        printf( "(%7.1f,%7.1f)\n", x, y );
        return FALSE;
    }


    if( ABS(dfGeoX) < 181 && ABS(dfGeoY) < 91 )
    {
        printf( "(%12.7f,%12.7f) ", dfGeoX, dfGeoY );
    }
    else
    {
        printf( "(%12.3f,%12.3f) ", dfGeoX, dfGeoY );
    }


    if( hTransform != NULL
        && OCTTransform(hTransform,1,&dfGeoX,&dfGeoY,NULL) )
    {

        printf( "(%s,", GDALDecToDMS( dfGeoX, "Long", 2 ) );
        printf( "%s)", GDALDecToDMS( dfGeoY, "Lat", 2 ) );
    }

    printf( "\n" );

    return TRUE;
}
