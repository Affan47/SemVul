pixOtsuThreshOnBackgroundNorm(PIX       *pixs,
                              PIX       *pixim,
                              l_int32    sx,
                              l_int32    sy,
                              l_int32    thresh,
                              l_int32    mincount,
                              l_int32    bgval,
                              l_int32    smoothx,
                              l_int32    smoothy,
                              l_float32  scorefract,
                              l_int32   *pthresh)
{
l_int32   w, h;
l_uint32  val;
PIX      *pixn, *pixt, *pixd;

    PROCNAME("pixOtsuThreshOnBackgroundNorm");

    if (pthresh) *pthresh = 0;
    if (!pixs || pixGetDepth(pixs) != 8)
        return (PIX *)ERROR_PTR("pixs undefined or not 8 bpp", procName, NULL);
    if (pixGetColormap(pixs))
        return (PIX *)ERROR_PTR("pixs is colormapped", procName, NULL);
    if (sx < 4 || sy < 4)
        return (PIX *)ERROR_PTR("sx and sy must be >= 4", procName, NULL);
    if (mincount > sx * sy) {
        L_WARNING("mincount too large for tile size\n", procName);
        mincount = (sx * sy) / 3;
    }

    pixn = pixBackgroundNorm(pixs, pixim, NULL, sx, sy, thresh,
                             mincount, bgval, smoothx, smoothy);
    if (!pixn)
        return (PIX *)ERROR_PTR("pixn not made", procName, NULL);


    pixGetDimensions(pixn, &w, &h, NULL);
    pixOtsuAdaptiveThreshold(pixn, w, h, 0, 0, scorefract, &pixt, &pixd);
    pixDestroy(&pixn);

    if (pixt && pthresh) {
        pixGetPixel(pixt, 0, 0, &val);
        *pthresh = val;
    }
    pixDestroy(&pixt);

    if (!pixd)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    else
        return pixd;
}
