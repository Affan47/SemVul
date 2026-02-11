ComputeAreaDiff(GInt32 nNodeXMin, GInt32 nNodeYMin,
                                          GInt32 nNodeXMax, GInt32 nNodeYMax,
                                          GInt32 nEntryXMin, GInt32 nEntryYMin,
                                          GInt32 nEntryXMax, GInt32 nEntryYMax)
{

    double dAreaDiff=0;

    double dNodeAreaBefore = MITAB_AREA(nNodeXMin,
                                        nNodeYMin,
                                        nNodeXMax,
                                        nNodeYMax);


    GBool bIsContained = (nEntryXMin >= nNodeXMin &&
                          nEntryYMin >= nNodeYMin &&
                          nEntryXMax <= nNodeXMax &&
                          nEntryYMax <= nNodeYMax );

    if (bIsContained)
    {


        dAreaDiff = MITAB_AREA(nEntryXMin, nEntryYMin,
                               nEntryXMax, nEntryYMax) - dNodeAreaBefore;
    }
    else
    {


        nNodeXMin = MIN(nNodeXMin, nEntryXMin);
        nNodeYMin = MIN(nNodeYMin, nEntryYMin);
        nNodeXMax = MAX(nNodeXMax, nEntryXMax);
        nNodeYMax = MAX(nNodeYMax, nEntryYMax);

        dAreaDiff = MITAB_AREA(nNodeXMin,nNodeYMin,
                               nNodeXMax,nNodeYMax) - dNodeAreaBefore;
    }

    return dAreaDiff;
}
