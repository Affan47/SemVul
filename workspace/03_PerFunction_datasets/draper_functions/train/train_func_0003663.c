numaQuantizeCrossingsByWindow(NUMA       *nas,
                              l_float32   ratio,
                              l_float32  *pwidth,
                              l_float32  *pfirstloc,
                              NUMA      **pnac,
                              l_int32     debugflag)
{
l_int32    i, nw, started, count, trans;
l_float32  minsize, minwidth, minshift, xfirst;
NUMA      *nac, *nad;

    PROCNAME("numaQuantizeCrossingsByWindow");

    if (!nas)
        return (NUMA *)ERROR_PTR("nas not defined", procName, NULL);
    if (numaGetCount(nas) < 2)
        return (NUMA *)ERROR_PTR("nas size < 2", procName, NULL);


    numaGetCrossingDistances(nas, NULL, NULL, &minsize, NULL);


    numaEvalBestWidthAndShift(nas, 100, 10, minsize, ratio * minsize,
                              &minwidth, &minshift, NULL);


    numaEvalBestWidthAndShift(nas, 100, 10, 0.98 * minwidth, 1.02 * minwidth,
                              &minwidth, &minshift, NULL);

    L_INFO("best width = %7.3f, best shift = %7.3f\n",
           procName, minwidth, minshift);


    numaEvalSyncError(nas, 0, 0, minwidth, minshift, NULL, &nac);
    if (pwidth) *pwidth = minwidth;
    if (pfirstloc) {
        numaGetFValue(nas, 0, &xfirst);
        *pfirstloc = xfirst + minshift;
    }


    nad = numaCreate(0);
    nw = numaGetCount(nac);
    started = FALSE;
    count = 0;
    for (i = 0; i < nw; i++) {
        numaGetIValue(nac, i, &trans);
        if (trans > 2)
            L_WARNING("trans = %d > 2 !!!\n", procName, trans);
        if (started) {
            if (trans > 1) {
                numaAddNumber(nad, count);
                trans--;
                count = 1;
            }
            if (trans == 1) {
                numaAddNumber(nad, count);
                count = 1;
            } else {
                count++;
            }
        }
        if (!started && trans) {
            started = TRUE;
            if (trans == 2)
                numaAddNumber(nad, 1);
            count = 1;
        }
    }

    if (pnac)
        *pnac = nac;
    else
        numaDestroy(&nac);
    return nad;
}
