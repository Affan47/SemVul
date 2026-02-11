IRasterIO( GDALRWFlag eRWFlag,
                                 int nXOff, int nYOff, int nXSize, int nYSize,
                                 void * pData, int nBufXSize, int nBufYSize,
                                 GDALDataType eBufType,
                                 int nPixelSpace, int nLineSpace )

{
    int         iSource;
    CPLErr      eErr = CE_None;

    if( eRWFlag == GF_Write )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Writing through VRTSourcedRasterBand is not supported." );
        return CE_Failure;
    }


    if ( bAntiRecursionFlag )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "VRTSourcedRasterBand::IRasterIO() called recursively on the same band. "
                  "It looks like the VRT is referencing itself." );
        return CE_Failure;
    }


    if( (nBufXSize < nXSize || nBufYSize < nYSize)
        && GetOverviewCount() > 0 )
    {
        if( OverviewRasterIO( eRWFlag, nXOff, nYOff, nXSize, nYSize,
                              pData, nBufXSize, nBufYSize,
                              eBufType, nPixelSpace, nLineSpace ) == CE_None )
            return CE_None;
    }


    if ( nPixelSpace == GDALGetDataTypeSize(eBufType)/8 &&
         (!bNoDataValueSet || (!CPLIsNan(dfNoDataValue) && dfNoDataValue == 0)) )
    {
        if (nLineSpace == nBufXSize * nPixelSpace)
        {
             memset( pData, 0, (GIntBig)nBufYSize * nLineSpace );
        }
        else
        {
            int    iLine;
            for( iLine = 0; iLine < nBufYSize; iLine++ )
            {
                memset( ((GByte*)pData) + (GIntBig)iLine * nLineSpace, 0, nBufXSize * nPixelSpace );
            }
        }
    }
    else if ( !bEqualAreas || bNoDataValueSet )
    {
        double dfWriteValue = 0.0;
        int    iLine;

        if( bNoDataValueSet )
            dfWriteValue = dfNoDataValue;

        for( iLine = 0; iLine < nBufYSize; iLine++ )
        {
            GDALCopyWords( &dfWriteValue, GDT_Float64, 0,
                           ((GByte *)pData) + (GIntBig)nLineSpace * iLine,
                           eBufType, nPixelSpace, nBufXSize );
        }
    }

    bAntiRecursionFlag = TRUE;


    for( iSource = 0; eErr == CE_None && iSource < nSources; iSource++ )
    {
        eErr =
            papoSources[iSource]->RasterIO( nXOff, nYOff, nXSize, nYSize,
                                            pData, nBufXSize, nBufYSize,
                                            eBufType, nPixelSpace, nLineSpace);
    }

    bAntiRecursionFlag = FALSE;

    return eErr;
}
