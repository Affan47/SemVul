IReadBlock( int nBlockXOff, int nBlockYOff,
                                  void * pImage )

{
    CPLAssert( nBlockXOff == 0 );

    if (psImage == NULL)
    {
        memset(pImage, 0, nBlockXSize);
        return CE_None;
    }

    if( panInterlaceMap != NULL )
        nBlockYOff = panInterlaceMap[nBlockYOff];

    memcpy( pImage, psImage->RasterBits + nBlockYOff * nBlockXSize,
            nBlockXSize );

    return CE_None;
}
