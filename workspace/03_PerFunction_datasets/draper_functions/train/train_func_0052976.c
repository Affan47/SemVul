fpixSampledDisparity(FPIX    *fpixs,
                     l_int32  sampling)
{
l_int32     w, h, wd, hd, i, j, is, js;
l_float32   val;
l_float32  *array;
FPIX       *fpixd;

    PROCNAME("fpixSampledDisparity");

    if (!fpixs)
        return (FPIX *)ERROR_PTR("fpixs not defined", procName, NULL);
    if (sampling < 1)
        return (FPIX *)ERROR_PTR("sampling < 1", procName, NULL);

    fpixGetDimensions(fpixs, &w, &h);
    wd = 1 + (w + sampling - 2) / sampling;
    hd = 1 + (h + sampling - 2) / sampling;
    if (wd < 3 || hd < 3)
        return (FPIX *)ERROR_PTR("wd < 3 or hd < 3", procName, NULL);
    if ((array = (l_float32 *)CALLOC(w, sizeof(l_float32))) == NULL)
        return (FPIX *)ERROR_PTR("calloc fail for array", procName, NULL);
    fpixd = fpixCreate(wd, hd);
    for (i = 0; i < hd; i++) {
        is = sampling * i;
        if (is >= h) continue;
        for (j = 0; j < wd; j++) {
            js = sampling * j;
            if (js >= w) continue;
            fpixGetPixel(fpixs, js, is, &val);
            fpixSetPixel(fpixd, j, i, val);
            array[j] = val;
        }

        fpixSetPixel(fpixd, wd - 1, i, 2 * array[wd - 1] - array[wd - 2]);
    }


    for (j = 0; j < wd; j++) {
        fpixGetPixel(fpixd, j, hd - 2, &val);
        fpixSetPixel(fpixd, j, hd - 1, val);
    }

    FREE(array);
    return fpixd;
}
