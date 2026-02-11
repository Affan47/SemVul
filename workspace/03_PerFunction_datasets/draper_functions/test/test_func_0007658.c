IReadBlock( int nBlockXOff, int nBlockYOff,
                                   void * pImage )

{
    ELASDataset	*poGDS = (ELASDataset *) poDS;
    CPLErr		eErr = CE_None;
    long		nOffset;
    int			nDataSize;

    CPLAssert( nBlockXOff == 0 );

    nDataSize = GDALGetDataTypeSize(eDataType) * poGDS->GetRasterXSize() / 8;
    nOffset = poGDS->nLineOffset * nBlockYOff + 1024 + (nBand-1) * nDataSize;


    if( VSIFSeekL( poGDS->fp, nOffset, SEEK_SET ) != 0
        || VSIFReadL( pImage, 1, nDataSize, poGDS->fp ) != (size_t) nDataSize )
    {
        CPLError( CE_Failure, CPLE_FileIO,
                  "Seek or read of %d bytes at %ld failed.\n",
                  nDataSize, nOffset );
        eErr = CE_Failure;
    }

    return eErr;
}
