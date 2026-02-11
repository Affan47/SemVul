numaCrossingsByThreshold(NUMA      *nax,
                         NUMA      *nay,
                         l_float32  thresh)
{
l_int32    i, n;
l_float32  startx, delx;
l_float32  xval1, xval2, yval1, yval2, delta1, delta2, crossval, fract;
NUMA      *nad;

    PROCNAME("numaCrossingsByThreshold");

    if (!nay)
        return (NUMA *)ERROR_PTR("nay not defined", procName, NULL);
    n = numaGetCount(nay);

    if (nax && (numaGetCount(nax) != n))
        return (NUMA *)ERROR_PTR("nax and nay sizes differ", procName, NULL);

    nad = numaCreate(0);
    numaGetFValue(nay, 0, &yval1);
    numaGetXParameters(nay, &startx, &delx);
    if (nax)
        numaGetFValue(nax, 0, &xval1);
    else
        xval1 = startx;
    for (i = 1; i < n; i++) {
        numaGetFValue(nay, i, &yval2);
        if (nax)
            numaGetFValue(nax, i, &xval2);
        else
            xval2 = startx + i * delx;
        delta1 = yval1 - thresh;
        delta2 = yval2 - thresh;
        if (delta1 == 0.0)
            numaAddNumber(nad, xval1);
        else if (delta2 == 0.0)
            numaAddNumber(nad, xval2);
        else if (delta1 * delta2 < 0.0) {
            fract = L_ABS(delta1) / L_ABS(yval1 - yval2);
            crossval = xval1 + fract * (xval2 - xval1);
            numaAddNumber(nad, crossval);
        }
        xval1 = xval2;
        yval1 = yval2;
    }

    return nad;
}
