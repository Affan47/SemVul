SBNSearchDiskTree( SBNSearchHandle hSBN,
                        double *padfBoundsMin, double *padfBoundsMax,
                        int *pnShapeCount )
{
    double dfMinX, dfMinY, dfMaxX, dfMaxY;
    double dfDiskXExtent, dfDiskYExtent;
    int bMinX, bMinY, bMaxX, bMaxY;

    *pnShapeCount = 0;

    dfMinX = padfBoundsMin[0];
    dfMinY = padfBoundsMin[1];
    dfMaxX = padfBoundsMax[0];
    dfMaxY = padfBoundsMax[1];

    if( dfMinX > dfMaxX || dfMinY > dfMaxY )
        return NULL;

    if( dfMaxX < hSBN->dfMinX || dfMaxY < hSBN->dfMinY ||
        dfMinX > hSBN->dfMaxX || dfMinY > hSBN->dfMaxY )
        return NULL;


    dfDiskXExtent = hSBN->dfMaxX - hSBN->dfMinX;
    dfDiskYExtent = hSBN->dfMaxY - hSBN->dfMinY;

    if ( dfDiskXExtent == 0.0 )
    {
        bMinX = 0;
        bMaxX = 255;
    }
    else
    {
        if( dfMinX < hSBN->dfMinX )
            bMinX = 0;
        else
        {
            double dfMinX_255 = (dfMinX - hSBN->dfMinX)
                                                    / dfDiskXExtent * 255.0;
            bMinX = (int)floor(dfMinX_255 - 0.005);
            if( bMinX < 0 ) bMinX = 0;
        }

        if( dfMaxX > hSBN->dfMaxX )
            bMaxX = 255;
        else
        {
            double dfMaxX_255 = (dfMaxX - hSBN->dfMinX)
                                                    / dfDiskXExtent * 255.0;
            bMaxX = (int)ceil(dfMaxX_255 + 0.005);
            if( bMaxX > 255 ) bMaxX = 255;
        }
    }

    if ( dfDiskYExtent == 0.0 )
    {
        bMinY = 0;
        bMaxY = 255;
    }
    else
    {
        if( dfMinY < hSBN->dfMinY )
            bMinY = 0;
        else
        {
            double dfMinY_255 = (dfMinY - hSBN->dfMinY)
                                                    / dfDiskYExtent * 255.0;
            bMinY = (int)floor(dfMinY_255 - 0.005);
            if( bMinY < 0 ) bMinY = 0;
        }

        if( dfMaxY > hSBN->dfMaxY )
            bMaxY = 255;
        else
        {
            double dfMaxY_255 = (dfMaxY - hSBN->dfMinY)
                                                    / dfDiskYExtent * 255.0;
            bMaxY = (int)ceil(dfMaxY_255 + 0.005);
            if( bMaxY > 255 ) bMaxY = 255;
        }
    }


    return SBNSearchDiskTreeInteger(hSBN,
                                    bMinX, bMinY, bMaxX, bMaxY,
                                    pnShapeCount);
}
