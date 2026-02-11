GDALWarpSrcAlphaMasker( void *pMaskFuncArg, int nBandCount, GDALDataType eType,
                        int nXOff, int nYOff, int nXSize, int nYSize,
                        GByte ** ,
                        int bMaskIsFloat, void *pValidityMask )

{
    GDALWarpOptions *psWO = (GDALWarpOptions *) pMaskFuncArg;
    float *pafMask = (float *) pValidityMask;


    if( !bMaskIsFloat )
    {
        CPLAssert( FALSE );
        return CE_Failure;
    }

    if( psWO == NULL || psWO->nSrcAlphaBand < 1 )
    {
        CPLAssert( FALSE );
        return CE_Failure;
    }


    CPLErr eErr;
    GDALRasterBandH hAlphaBand = GDALGetRasterBand( psWO->hSrcDS,
                                                    psWO->nSrcAlphaBand );
    if (hAlphaBand == NULL)
        return CE_Failure;

    eErr = GDALRasterIO( hAlphaBand, GF_Read, nXOff, nYOff, nXSize, nYSize,
                         pafMask, nXSize, nYSize, GDT_Float32, 0, 0 );

    if( eErr != CE_None )
        return eErr;


    for( int iPixel = nXSize * nYSize - 1; iPixel >= 0; iPixel-- )
    {
        pafMask[iPixel] = (float)( pafMask[iPixel] * 0.00392157 );
        pafMask[iPixel] = MIN( 1.0F, pafMask[iPixel] );
    }

    return CE_None;
}
