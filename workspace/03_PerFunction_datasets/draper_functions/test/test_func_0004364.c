ScanForGCPs_MERIS()

{
    int		nDatasetIndex, nNumDSR, nDSRSize, iRecord;


    nDatasetIndex = EnvisatFile_GetDatasetIndex( hEnvisatFile,
                                                 "Tie points ADS" );
    if( nDatasetIndex == -1 )
        return;

    if( EnvisatFile_GetDatasetInfo( hEnvisatFile, nDatasetIndex,
                                    NULL, NULL, NULL, NULL, NULL,
                                    &nNumDSR, &nDSRSize ) != SUCCESS )
        return;

    if( nNumDSR == 0 )
        return;


    int  nLinesPerTiePoint, nSamplesPerTiePoint;
    int  nTPPerLine, nTPPerColumn = nNumDSR;

    if( nNumDSR == 0 )
        return;

    nLinesPerTiePoint =
        EnvisatFile_GetKeyValueAsInt( hEnvisatFile, SPH,
                                      "LINES_PER_TIE_PT", 0 );
    nSamplesPerTiePoint =
        EnvisatFile_GetKeyValueAsInt( hEnvisatFile, SPH,
                                      "SAMPLES_PER_TIE_PT", 0 );

    if( nLinesPerTiePoint == 0 || nSamplesPerTiePoint == 0 )
        return;

    nTPPerLine = (GetRasterXSize() + nSamplesPerTiePoint - 1)
        / nSamplesPerTiePoint;

    if( (GetRasterYSize() + nLinesPerTiePoint - 1)
        / nLinesPerTiePoint != nTPPerColumn )
    {
        CPLDebug( "EnvisatDataset", "Got %d instead of %d nTPPerColumn.",
                  (GetRasterYSize()+nLinesPerTiePoint-1)/nLinesPerTiePoint,
                  nTPPerColumn );
        return;
    }

    if( 50*nTPPerLine + 13 != nDSRSize )
    {
        CPLDebug( "EnvisatDataset",
                  "DSRSize=%d instead of expected %d for tiepoints ADS.",
                  nDSRSize, 50*nTPPerLine + 13 );
        return;
    }


    GByte	*pabyRecord = (GByte *) CPLMalloc(nDSRSize);
    int  	iGCP;
    GUInt32 	unValue;

    nGCPCount = 0;
    pasGCPList = (GDAL_GCP *)
        CPLCalloc(sizeof(GDAL_GCP),nNumDSR * nTPPerLine);

    for( iRecord = 0; iRecord < nNumDSR; iRecord++ )
    {
        if( EnvisatFile_ReadDatasetRecord( hEnvisatFile, nDatasetIndex,
                                           iRecord, pabyRecord ) != SUCCESS )
            continue;

        memcpy( &unValue, pabyRecord + 13, 4 );

        for( iGCP = 0; iGCP < nTPPerLine; iGCP++ )
        {
            char	szId[128];

            GDALInitGCPs( 1, pasGCPList + nGCPCount );

            CPLFree( pasGCPList[nGCPCount].pszId );

            sprintf( szId, "%d", nGCPCount+1 );
            pasGCPList[nGCPCount].pszId = CPLStrdup( szId );

            memcpy( &unValue, pabyRecord + 13 + nTPPerLine*4 + iGCP*4, 4 );
            pasGCPList[nGCPCount].dfGCPX =
                ((int)CPL_MSBWORD32(unValue))*0.000001;

            memcpy( &unValue, pabyRecord + 13 + iGCP*4, 4 );
            pasGCPList[nGCPCount].dfGCPY =
                ((int)CPL_MSBWORD32(unValue))*0.000001;

            pasGCPList[nGCPCount].dfGCPZ = 0.0;

            pasGCPList[nGCPCount].dfGCPLine = iRecord*nLinesPerTiePoint + 0.5;
            pasGCPList[nGCPCount].dfGCPPixel = iGCP*nSamplesPerTiePoint + 0.5;

            nGCPCount++;
        }
    }
    CPLFree( pabyRecord );
}
