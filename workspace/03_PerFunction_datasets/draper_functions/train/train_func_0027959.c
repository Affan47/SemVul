IReadBlock( int nBlockXOff, int nBlockYOff,
                                  void * pImage )

{
    WEBPDataset* poGDS = (WEBPDataset*) poDS;

    if( poGDS->Uncompress() != CE_None )
        return CE_Failure;

    int i;
    GByte* pabyUncompressed =
        &poGDS->pabyUncompressed[nBlockYOff * nRasterXSize  * poGDS->nBands + nBand - 1];
    for(i=0;i<nRasterXSize;i++)
        ((GByte*)pImage)[i] = pabyUncompressed[poGDS->nBands * i];

    return CE_None;
}
