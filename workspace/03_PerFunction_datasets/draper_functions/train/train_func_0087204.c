DGNPointToInt( DGNInfo *psDGN, DGNPoint *psPoint,
                           unsigned char *pabyTarget )

{
    double     adfCT[3];
    int        i;

    adfCT[0] = psPoint->x;
    adfCT[1] = psPoint->y;
    adfCT[2] = psPoint->z;

    for( i = 0; i < psDGN->dimension; i++ )
    {
        GInt32 nCTI;
        unsigned char *pabyCTI = (unsigned char *) &nCTI;

        nCTI = (GInt32) MAX(-2147483647,MIN(2147483647,adfCT[i]));

#ifdef WORDS_BIGENDIAN
        pabyTarget[i*4+0] = pabyCTI[1];
        pabyTarget[i*4+1] = pabyCTI[0];
        pabyTarget[i*4+2] = pabyCTI[3];
        pabyTarget[i*4+3] = pabyCTI[2];
#else
        pabyTarget[i*4+3] = pabyCTI[1];
        pabyTarget[i*4+2] = pabyCTI[0];
        pabyTarget[i*4+1] = pabyCTI[3];
        pabyTarget[i*4+0] = pabyCTI[2];
#endif
    }
}
