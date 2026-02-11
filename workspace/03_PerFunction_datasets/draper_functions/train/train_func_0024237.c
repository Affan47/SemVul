IReadBlock( int nBlockXOff, int nBlockYOff,
                                      void * pImage )

{
    BSBDataset *poGDS = (BSBDataset *) poDS;
    GByte *pabyScanline = (GByte*) pImage;

    if( BSBReadScanline( poGDS->psInfo, nBlockYOff, pabyScanline ) )
    {
        for( int i = 0; i < nBlockXSize; i++ )
        {


            if (pabyScanline[i] > 0)
                pabyScanline[i] -= 1;
        }

        return CE_None;
    }
    else
        return CE_Failure;
}
