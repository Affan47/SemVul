AccessLine( int iLine )

{
    if (pLineBuffer == NULL)
        return CE_Failure;

    if( nLoadedScanline == iLine )
        return CE_None;


    vsi_l_offset nReadStart;
    if( nPixelOffset >= 0 )
        nReadStart = nImgOffset + (vsi_l_offset)iLine * nLineOffset;
    else
    {
        nReadStart = nImgOffset + (vsi_l_offset)iLine * nLineOffset
            - ABS(nPixelOffset) * (nBlockXSize-1);
    }


    if( Seek(nReadStart, SEEK_SET) == -1 )
    {
        if (poDS != NULL && poDS->GetAccess() == GA_ReadOnly)
        {
            CPLError( CE_Failure, CPLE_FileIO,
                  "Failed to seek to scanline %d @ %d.\n",
                  iLine, (int) (nImgOffset + (vsi_l_offset)iLine * nLineOffset) );
            return CE_Failure;
        }
        else
        {
            memset( pLineBuffer, 0, nPixelOffset * nBlockXSize );
            nLoadedScanline = iLine;
            return CE_None;
        }
    }


    int	nBytesToRead, nBytesActuallyRead;

    nBytesToRead = ABS(nPixelOffset) * (nBlockXSize - 1)
        + GDALGetDataTypeSize(GetRasterDataType()) / 8;

    nBytesActuallyRead = Read( pLineBuffer, 1, nBytesToRead );
    if( nBytesActuallyRead < nBlockXSize )
    {
        if (poDS != NULL && poDS->GetAccess() == GA_ReadOnly)
        {
            CPLError( CE_Failure, CPLE_FileIO,
                      "Failed to read scanline %d.\n",
                      iLine);
            return CE_Failure;
        }
        else
        {
            memset( ((GByte *) pLineBuffer) + nBytesActuallyRead,
                    0, nBytesToRead - nBytesActuallyRead );
        }
    }


    if( !bNativeOrder && eDataType != GDT_Byte )
    {
        if( GDALDataTypeIsComplex( eDataType ) )
        {
            int nWordSize;

            nWordSize = GDALGetDataTypeSize(eDataType)/16;
            GDALSwapWords( pLineBuffer, nWordSize, nBlockXSize, ABS(nPixelOffset) );
            GDALSwapWords( ((GByte *) pLineBuffer)+nWordSize,
                           nWordSize, nBlockXSize, ABS(nPixelOffset) );
        }
        else
            GDALSwapWords( pLineBuffer, GDALGetDataTypeSize(eDataType)/8,
                           nBlockXSize, ABS(nPixelOffset) );
    }

    nLoadedScanline = iLine;

    return CE_None;
}
