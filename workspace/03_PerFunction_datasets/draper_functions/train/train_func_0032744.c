IReadBlock( int nBlockXOff, int nBlockYOff,
                                  void * pImage )

{
    PNGDataset	*poGDS = (PNGDataset *) poDS;
    CPLErr      eErr;
    GByte       *pabyScanline;
    int         i, nPixelSize, nPixelOffset, nXSize = GetXSize();

    CPLAssert( nBlockXOff == 0 );

    if( poGDS->nBitDepth == 16 )
        nPixelSize = 2;
    else
        nPixelSize = 1;


    if (poGDS->fpImage == NULL)
    {
        memset( pImage, 0, nPixelSize * nXSize );
        return CE_None;
    }

    nPixelOffset = poGDS->nBands * nPixelSize;


    eErr = poGDS->LoadScanline( nBlockYOff );
    if( eErr != CE_None )
        return eErr;

    pabyScanline = poGDS->pabyBuffer
        + (nBlockYOff - poGDS->nBufferStartLine) * nPixelOffset * nXSize
        + nPixelSize * (nBand - 1);


    if( nPixelSize == nPixelOffset )
        memcpy( pImage, pabyScanline, nPixelSize * nXSize );
    else if( nPixelSize == 1 )
    {
        for( i = 0; i < nXSize; i++ )
            ((GByte *) pImage)[i] = pabyScanline[i*nPixelOffset];
    }
    else
    {
        CPLAssert( nPixelSize == 2 );
        for( i = 0; i < nXSize; i++ )
        {
            ((GUInt16 *) pImage)[i] =
                *((GUInt16 *) (pabyScanline+i*nPixelOffset));
        }
    }


    int iBand;
    for(iBand = 1; iBand < poGDS->GetRasterCount(); iBand++)
    {
        GDALRasterBlock *poBlock;

        poBlock =
            poGDS->GetRasterBand(iBand+1)->GetLockedBlockRef(nBlockXOff,nBlockYOff);
        if( poBlock != NULL )
            poBlock->DropLock();
    }

    return CE_None;
}
