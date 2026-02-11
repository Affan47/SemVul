VRTWarpedOverviewTransform( void *pTransformArg, int bDstToSrc,
                                int nPointCount,
                                double *padfX, double *padfY, double *padfZ,
                                int *panSuccess )

{
    VWOTInfo *psInfo = (VWOTInfo *) pTransformArg;
    int i, bSuccess;

    if( bDstToSrc )
    {
        for( i = 0; i < nPointCount; i++ )
        {
            padfX[i] *= psInfo->dfXOverviewFactor;
            padfY[i] *= psInfo->dfYOverviewFactor;
        }
    }

    bSuccess = psInfo->pfnBaseTransformer( psInfo->pBaseTransformerArg,
                                           bDstToSrc,
                                           nPointCount, padfX, padfY, padfZ,
                                           panSuccess );

    if( !bDstToSrc )
    {
        for( i = 0; i < nPointCount; i++ )
        {
            padfX[i] /= psInfo->dfXOverviewFactor;
            padfY[i] /= psInfo->dfYOverviewFactor;
        }
    }

    return bSuccess;
}
