pixGetLocalSkewTransform(PIX       *pixs,
                         l_int32    nslices,
                         l_int32    redsweep,
                         l_int32    redsearch,
                         l_float32  sweeprange,
                         l_float32  sweepdelta,
                         l_float32  minbsdelta,
                         PTA      **pptas,
                         PTA      **pptad)
{
l_int32    w, h, i;
l_float32  deg2rad, angr, angd, dely;
NUMA      *naskew;
PTA       *ptas, *ptad;

    PROCNAME("pixGetLocalSkewTransform");

    if (!pptas || !pptad)
        return ERROR_INT("&ptas and &ptad not defined", procName, 1);
    *pptas = *pptad = NULL;
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    if (nslices < 2 || nslices > 20)
        nslices = DEFAULT_SLICES;
    if (redsweep < 1 || redsweep > 8)
        redsweep = DEFAULT_SWEEP_REDUCTION;
    if (redsearch < 1 || redsearch > redsweep)
        redsearch = DEFAULT_BS_REDUCTION;
    if (sweeprange == 0.0)
        sweeprange = DEFAULT_SWEEP_RANGE;
    if (sweepdelta == 0.0)
        sweepdelta = DEFAULT_SWEEP_DELTA;
    if (minbsdelta == 0.0)
        minbsdelta = DEFAULT_MINBS_DELTA;

    naskew = pixGetLocalSkewAngles(pixs, nslices, redsweep, redsearch,
                                   sweeprange, sweepdelta, minbsdelta,
                                   NULL, NULL);
    if (!naskew)
        return ERROR_INT("naskew not made", procName, 1);

    deg2rad = 3.14159265 / 180.;
    w = pixGetWidth(pixs);
    h = pixGetHeight(pixs);
    ptas = ptaCreate(4);
    ptad = ptaCreate(4);
    *pptas = ptas;
    *pptad = ptad;


    for (i = 0; i < h; i++) {
        numaGetFValue(naskew, i, &angd);
        angr = angd * deg2rad;
        dely = w * tan(angr);
        if (i - dely > 0.05 * h)
            break;
    }
    ptaAddPt(ptas, 0, i);
    ptaAddPt(ptas, w - 1, i - dely);
    ptaAddPt(ptad, 0, i);
    ptaAddPt(ptad, w - 1, i);


    for (i = h - 1; i > 0; i--) {
        numaGetFValue(naskew, i, &angd);
        angr = angd * deg2rad;
        dely = w * tan(angr);
        if (i - dely < 0.95 * h)
            break;
    }
    ptaAddPt(ptas, 0, i);
    ptaAddPt(ptas, w - 1, i - dely);
    ptaAddPt(ptad, 0, i);
    ptaAddPt(ptad, w - 1, i);

    numaDestroy(&naskew);
    return 0;
}
