IRasterIO( GDALRWFlag eRWFlag,
                                 int nXOff, int nYOff, int nXSize, int nYSize,
                                 void * pData, int nBufXSize, int nBufYSize,
                                 GDALDataType eBufType,
                                 int nPixelSpace, int nLineSpace )

{
    if( poRawRaster == NULL )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "No raw raster band configured on VRTRawRasterBand." );
        return CE_Failure;
    }

    if( eRWFlag == GF_Write && eAccess == GA_ReadOnly )
    {
        CPLError( CE_Failure, CPLE_NoWriteAccess,
                  "Attempt to write to read only dataset in"
                  "VRTRawRasterBand::IRasterIO().\n" );

        return( CE_Failure );
    }


    if( (nBufXSize < nXSize || nBufYSize < nYSize)
        && GetOverviewCount() > 0 )
    {
        if( OverviewRasterIO( eRWFlag, nXOff, nYOff, nXSize, nYSize,
                              pData, nBufXSize, nBufYSize,
                              eBufType, nPixelSpace, nLineSpace ) == CE_None )
            return CE_None;
    }

    poRawRaster->SetAccess(eAccess);

    return poRawRaster->RasterIO( eRWFlag, nXOff, nYOff, nXSize, nYSize,
                                  pData, nBufXSize, nBufYSize,
                                  eBufType, nPixelSpace, nLineSpace );
}
