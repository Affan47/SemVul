ProcessModisSDSGeolocation(void)

{
    int iDSIndex, iXIndex=-1, iYIndex=-1;


    if( EQUAL(szName,"longitude") || EQUAL(szName,"latitude") )
        return;

    if (nRasterYSize == 1)
        return;


    int32   nDatasets, nAttributes;

    if ( SDfileinfo( hSD, &nDatasets, &nAttributes ) != 0 )
	return;

    for( iDSIndex = 0; iDSIndex < nDatasets; iDSIndex++ )
    {
        int32	    iRank, iNumType, nAttrs, iSDS;
        char        szName[HDF4_SDS_MAXNAMELEN];
        int32       aiDimSizes[H4_MAX_VAR_DIMS];

	iSDS = SDselect( hSD, iDSIndex );

	if( SDgetinfo( iSDS, szName, &iRank, aiDimSizes, &iNumType,
                       &nAttrs) == 0 )
        {
            if( EQUAL(szName,"latitude") )
                iYIndex = iDSIndex;

            if( EQUAL(szName,"longitude") )
                iXIndex = iDSIndex;
        }

        SDendaccess(iSDS);
    }

    if( iXIndex == -1 || iYIndex == -1 )
        return;


    CPLString  osWrk;

    SetMetadataItem( "SRS", SRS_WKT_WGS84, "GEOLOCATION" );

    osWrk.Printf( "HDF4_SDS:UNKNOWN:\"%s\":%d",
                  pszFilename, iXIndex );
    SetMetadataItem( "X_DATASET", osWrk, "GEOLOCATION" );
    SetMetadataItem( "X_BAND", "1" , "GEOLOCATION" );

    osWrk.Printf( "HDF4_SDS:UNKNOWN:\"%s\":%d",
                  pszFilename, iYIndex );
    SetMetadataItem( "Y_DATASET", osWrk, "GEOLOCATION" );
    SetMetadataItem( "Y_BAND", "1" , "GEOLOCATION" );

    SetMetadataItem( "PIXEL_OFFSET", "0", "GEOLOCATION" );
    SetMetadataItem( "PIXEL_STEP", "1", "GEOLOCATION" );

    SetMetadataItem( "LINE_OFFSET", "0", "GEOLOCATION" );
    SetMetadataItem( "LINE_STEP", "1", "GEOLOCATION" );
}
