gvBurnPoint( void *pCBData, int nY, int nX, double dfVariant )

{
    GDALRasterizeInfo *psInfo = (GDALRasterizeInfo *) pCBData;
    int iBand;

    CPLAssert( nY >= 0 && nY < psInfo->nYSize );
    CPLAssert( nX >= 0 && nX < psInfo->nXSize );

    if( psInfo->eType == GDT_Byte )
    {
        for( iBand = 0; iBand < psInfo->nBands; iBand++ )
        {
            unsigned char *pbyInsert = psInfo->pabyChunkBuf
                                      + iBand * psInfo->nXSize * psInfo->nYSize
                                      + nY * psInfo->nXSize + nX;

            *pbyInsert = (unsigned char)( psInfo->padfBurnValue[iBand] +
                          ( (psInfo->eBurnValueSource == GBV_UserBurnValue)?
                             0 : dfVariant ) );
        }
    }
    else if( psInfo->eType == GDT_Float64 )
    {
        for( iBand = 0; iBand < psInfo->nBands; iBand++ )
        {
            double   *pdfInsert = ((double *) psInfo->pabyChunkBuf)
                                + iBand * psInfo->nXSize * psInfo->nYSize
                                + nY * psInfo->nXSize + nX;

            *pdfInsert = ( psInfo->padfBurnValue[iBand] +
                         ( (psInfo->eBurnValueSource == GBV_UserBurnValue)?
                            0 : dfVariant ) );
        }
    }
    else
        CPLAssert(0);
}
