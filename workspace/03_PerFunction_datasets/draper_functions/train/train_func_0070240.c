FeedLine( double *padfScanline )

{


    double *padfTempLine = padfLastLine;
    padfLastLine = padfThisLine;
    padfThisLine = padfTempLine;


    if( padfScanline == NULL )
    {
        memcpy( padfThisLine, padfLastLine, sizeof(double) * nWidth );
    }
    else
    {
        memcpy( padfThisLine, padfScanline, sizeof(double) * nWidth );
    }


    int iPixel;

    for( iPixel = 0; iPixel < nWidth; iPixel++ )
    {
        if( bNoDataActive && padfThisLine[iPixel] == dfNoDataValue )
            continue;

        double dfLevel = (padfThisLine[iPixel] - dfContourOffset)
            / dfContourInterval;

        if( dfLevel - (int) dfLevel == 0.0 )
        {
            padfThisLine[iPixel] += dfContourInterval * FUDGE_EXACT;
        }
    }


    if( iLine == -1 )
    {
        memcpy( padfLastLine, padfThisLine, sizeof(double) * nWidth );
        iLine = 0;
    }


    int iLevel, iContour;

    for( iLevel = 0; iLevel < nLevelCount; iLevel++ )
    {
        GDALContourLevel *poLevel = papoLevels[iLevel];

        for( iContour = 0; iContour < poLevel->GetContourCount(); iContour++ )
            poLevel->GetContour( iContour )->bRecentlyAccessed = FALSE;
    }


    for( iPixel = 0; iPixel < nWidth+1; iPixel++ )
    {
        CPLErr eErr = ProcessPixel( iPixel );
        if( eErr != CE_None )
            return eErr;
    }


    CPLErr eErr = EjectContours( padfScanline != NULL );

    iLine++;

    if( iLine == nHeight && eErr == CE_None )
        return FeedLine( NULL );
    else
        return eErr;
}
