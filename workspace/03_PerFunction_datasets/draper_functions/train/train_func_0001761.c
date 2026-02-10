IWriteBlock( int nBlockXOff, int nBlockYOff,
                                   void * pImage )
{
    BMPDataset  *poGDS = (BMPDataset *)poDS;
    int         iInPixel, iOutPixel;
    GUInt32     iScanOffset;

    CPLAssert( poGDS != NULL
               && nBlockXOff >= 0
               && nBlockYOff >= 0
               && pImage != NULL );

    iScanOffset = poGDS->sFileHeader.iOffBits +
            ( poGDS->GetRasterYSize() - nBlockYOff - 1 ) * nScanSize;
    if ( VSIFSeekL( poGDS->fp, iScanOffset, SEEK_SET ) < 0 )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Can't seek to offset %ld in output file to write data.\n%s",
                  (long) iScanOffset, VSIStrerror( errno ) );
        return CE_Failure;
    }

    if( poGDS->nBands != 1 )
    {
        memset( pabyScan, 0, nScanSize );
        VSIFReadL( pabyScan, 1, nScanSize, poGDS->fp );
        VSIFSeekL( poGDS->fp, iScanOffset, SEEK_SET );
    }

    for ( iInPixel = 0, iOutPixel = iBytesPerPixel - nBand;
          iInPixel < nBlockXSize; iInPixel++, iOutPixel += poGDS->nBands )
    {
        pabyScan[iOutPixel] = ((GByte *) pImage)[iInPixel];
    }

    if ( VSIFWriteL( pabyScan, 1, nScanSize, poGDS->fp ) < nScanSize )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Can't write block with X offset %d and Y offset %d.\n%s",
                  nBlockXOff, nBlockYOff,
                  VSIStrerror( errno ) );
        return CE_Failure;
    }

    return CE_None;
}
