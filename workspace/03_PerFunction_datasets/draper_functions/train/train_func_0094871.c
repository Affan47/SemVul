IReadBlock( int nBlockXOff,
                                      int nBlockYOff,
                                      void *pImage )
{
    if( IntergraphRasterBand::IReadBlock( nBlockXOff,
                                          nBlockYOff,
                                          pImage ) != CE_None )
    {
        return CE_Failure;
    }


    int i, j;

    for ( i = 0, j = ( nRGBIndex - 1 );
          i < ( nBlockXSize * nBlockYSize );
          i++, j += 3 )
    {
        ( (GByte*) pImage )[i] = pabyBlockBuf[j];
    }

    return CE_None;
}
