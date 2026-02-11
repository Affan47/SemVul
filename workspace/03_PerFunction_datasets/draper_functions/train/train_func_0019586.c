pixNumSignificantGrayColors(PIX       *pixs,
                            l_int32    darkthresh,
                            l_int32    lightthresh,
                            l_float32  minfract,
                            l_int32    factor,
                            l_int32   *pncolors)
{
l_int32  i, w, h, count, mincount, ncolors;
NUMA    *na;

    PROCNAME("pixNumSignificantGrayColors");

    if (!pncolors)
        return ERROR_INT("&ncolors not defined", procName, 1);
    *pncolors = 0;
    if (!pixs || pixGetDepth(pixs) != 8)
        return ERROR_INT("pixs not defined or not 8 bpp", procName, 1);
    if (darkthresh < 0) darkthresh = 20;
    if (lightthresh < 0) lightthresh = 236;
    if (minfract < 0.0) minfract = 0.0001;
    if (minfract > 1.0)
        return ERROR_INT("minfract > 1.0", procName, 1);
    if (lightthresh > 255 || darkthresh >= lightthresh)
        return ERROR_INT("invalid thresholds", procName, 1);
    if (factor < 1) factor = 1;

    pixGetDimensions(pixs, &w, &h, NULL);
    mincount = (l_int32)(minfract * w * h);
    if ((na = pixGetGrayHistogram(pixs, factor)) == NULL)
        return ERROR_INT("na not made", procName, 1);
    ncolors = 2;
    for (i = darkthresh; i <= lightthresh; i++) {
        numaGetIValue(na, i, &count);
        if (count >= mincount)
            ncolors++;
    }

    *pncolors = ncolors;
    numaDestroy(&na);
    return 0;
}
