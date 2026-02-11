IReadBlock( int nBlockXOff, int nBlockYOff,
				void *pImage )
{
    GFFDataset *poGDS = (GFFDataset *)poDS;
    long nOffset = poGDS->nLength;

    VSIFSeekL(poGDS->fp, nOffset + (poGDS->GetRasterXSize() * nBlockYOff * (nSampleSize)),SEEK_SET);


    if (VSIFReadL(pImage,nRasterBandMemory,1,poGDS->fp) != 1)
        return CE_Failure;

#if defined(CPL_MSB)
    if( GDALDataTypeIsComplex( eDataType ) )
    {
        int nWordSize;

        nWordSize = GDALGetDataTypeSize(eDataType)/16;
        GDALSwapWords( pImage, nWordSize, nBlockXSize, 2*nWordSize );
        GDALSwapWords( ((GByte *) pImage)+nWordSize,
                        nWordSize, nBlockXSize, 2*nWordSize );
    }
#endif

    return CE_None;

}
