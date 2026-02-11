GDALdllImagePoint( int nRasterXSize, int nRasterYSize,
                        int nPartCount, int *panPartSize,
                        double *padfX, double *padfY, double *padfVariant,
                        llPointFunc pfnPointFunc, void *pCBData )
{
    int     i;

    for ( i = 0; i < nPartCount; i++ )
    {
        int nX = (int)floor( padfX[i] );
        int nY = (int)floor( padfY[i] );
        double dfVariant = 0;
        if( padfVariant != NULL )
            dfVariant = padfVariant[i];

        if ( 0 <= nX && nX < nRasterXSize && 0 <= nY && nY < nRasterYSize )
            pfnPointFunc( pCBData, nY, nX, dfVariant );
    }
}
