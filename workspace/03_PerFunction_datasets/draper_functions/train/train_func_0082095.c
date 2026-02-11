pixGetGrayHistogramMasked(PIX        *pixs,
                          PIX        *pixm,
                          l_int32     x,
                          l_int32     y,
                          l_int32     factor)
{
l_int32     i, j, w, h, wm, hm, dm, wplg, wplm, val;
l_uint32   *datag, *datam, *lineg, *linem;
l_float32  *array;
NUMA       *na;
PIX        *pixg;

    PROCNAME("pixGetGrayHistogramMasked");

    if (!pixm)
        return pixGetGrayHistogram(pixs, factor);

    if (!pixs)
        return (NUMA *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 8 && !pixGetColormap(pixs))
        return (NUMA *)ERROR_PTR("pixs neither 8 bpp nor colormapped",
                                 procName, NULL);
    pixGetDimensions(pixm, &wm, &hm, &dm);
    if (dm != 1)
        return (NUMA *)ERROR_PTR("pixm not 1 bpp", procName, NULL);
    if (factor < 1)
        return (NUMA *)ERROR_PTR("sampling factor < 1", procName, NULL);

    if ((na = numaCreate(256)) == NULL)
        return (NUMA *)ERROR_PTR("na not made", procName, NULL);
    numaSetCount(na, 256);
    array = numaGetFArray(na, L_NOCOPY);

    if (pixGetColormap(pixs))
        pixg = pixRemoveColormap(pixs, REMOVE_CMAP_TO_GRAYSCALE);
    else
        pixg = pixClone(pixs);
    pixGetDimensions(pixg, &w, &h, NULL);
    datag = pixGetData(pixg);
    wplg = pixGetWpl(pixg);
    datam = pixGetData(pixm);
    wplm = pixGetWpl(pixm);


    for (i = 0; i < hm; i += factor) {
        if (y + i < 0 || y + i >= h) continue;
        lineg = datag + (y + i) * wplg;
        linem = datam + i * wplm;
        for (j = 0; j < wm; j += factor) {
            if (x + j < 0 || x + j >= w) continue;
            if (GET_DATA_BIT(linem, j)) {
                val = GET_DATA_BYTE(lineg, x + j);
                array[val] += 1.0;
            }
        }
    }

    pixDestroy(&pixg);
    return na;
}
