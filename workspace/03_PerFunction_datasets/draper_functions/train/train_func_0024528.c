AIGProcessRaw1BitBlock( GByte *pabyCur, int nDataSize, int nMin,
                               int nBlockXSize, int nBlockYSize,
                               GInt32 * panData )

{
    int		i;

    if( nDataSize < (nBlockXSize*nBlockYSize+7)/8 )
    {
        CPLError(CE_Failure, CPLE_AppDefined, "Block too small");
        return CE_Failure;
    }


    for( i = 0; i < nBlockXSize * nBlockYSize; i++ )
    {
        if( pabyCur[i>>3] & (0x80 >> (i&0x7)) )
            panData[i] = 1 + nMin;
        else
            panData[i] = 0 + nMin;
    }

    return( CE_None );
}
