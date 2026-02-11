pixDeskewLocal(PIX       *pixs,
               l_int32    nslices,
               l_int32    redsweep,
               l_int32    redsearch,
               l_float32  sweeprange,
               l_float32  sweepdelta,
               l_float32  minbsdelta)
{
l_int32    ret;
PIX       *pixd;
PTA       *ptas, *ptad;

    PROCNAME("pixDeskewLocal");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);


    ret = pixGetLocalSkewTransform(pixs, nslices, redsweep, redsearch,
                                   sweeprange, sweepdelta, minbsdelta,
                                   &ptas, &ptad);
    if (ret != 0)
        return (PIX *)ERROR_PTR("transform pts not found", procName, NULL);


    pixd = pixProjectiveSampledPta(pixs, ptad, ptas, L_BRING_IN_WHITE);

    ptaDestroy(&ptas);
    ptaDestroy(&ptad);
    return pixd;
}
