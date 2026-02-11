GDALFilterLine( float *pafLastLine, float *pafThisLine, float *pafNextLine,
                float *pafOutLine,
                GByte *pabyLastTMask, GByte *pabyThisTMask, GByte*pabyNextTMask,
                GByte *pabyThisFMask, int nXSize )

{
    int iX;

    for( iX = 0; iX < nXSize; iX++ )
    {
        if( !pabyThisFMask[iX] )
        {
            pafOutLine[iX] = pafThisLine[iX];
            continue;
        }

        CPLAssert( pabyThisTMask[iX] );

        double dfValSum = 0.0;
        double dfWeightSum = 0.0;


        if( pafLastLine != NULL )
        {
            if( iX > 0 && pabyLastTMask[iX-1] )
            {
                dfValSum += pafLastLine[iX-1];
                dfWeightSum += 1.0;
            }
            if( pabyLastTMask[iX] )
            {
                dfValSum += pafLastLine[iX];
                dfWeightSum += 1.0;
            }
            if( iX < nXSize-1 && pabyLastTMask[iX+1] )
            {
                dfValSum += pafLastLine[iX+1];
                dfWeightSum += 1.0;
            }
        }


        if( iX > 0 && pabyThisTMask[iX-1] )
        {
            dfValSum += pafThisLine[iX-1];
            dfWeightSum += 1.0;
        }
        if( pabyThisTMask[iX] )
        {
            dfValSum += pafThisLine[iX];
            dfWeightSum += 1.0;
        }
        if( iX < nXSize-1 && pabyThisTMask[iX+1] )
        {
            dfValSum += pafThisLine[iX+1];
            dfWeightSum += 1.0;
        }


        if( pafNextLine != NULL )
        {
            if( iX > 0 && pabyNextTMask[iX-1] )
            {
                dfValSum += pafNextLine[iX-1];
                dfWeightSum += 1.0;
            }
            if( pabyNextTMask[iX] )
            {
                dfValSum += pafNextLine[iX];
                dfWeightSum += 1.0;
            }
            if( iX < nXSize-1 && pabyNextTMask[iX+1] )
            {
                dfValSum += pafNextLine[iX+1];
                dfWeightSum += 1.0;
            }
        }

        pafOutLine[iX] = (float) (dfValSum / dfWeightSum);
    }
}
