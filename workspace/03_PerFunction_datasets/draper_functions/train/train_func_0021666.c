ptaGetLinearLSF(PTA        *pta,
                l_float32  *pa,
                l_float32  *pb,
                NUMA      **pnafit)
{
l_int32     n, i;
l_float32   factor, sx, sy, sxx, sxy, val;
l_float32  *xa, *ya;

    PROCNAME("ptaGetLinearLSF");

    if (!pa && !pb)
        return ERROR_INT("neither &a nor &b are defined", procName, 1);
    if (pa) *pa = 0.0;
    if (pb) *pb = 0.0;
    if (pnafit) *pnafit = NULL;
    if (!pta)
        return ERROR_INT("pta not defined", procName, 1);
    if ((n = ptaGetCount(pta)) < 2)
        return ERROR_INT("less than 2 pts found", procName, 1);

    xa = pta->x;
    ya = pta->y;

    sx = sy = sxx = sxy = 0.;
    if (pa && pb) {
        for (i = 0; i < n; i++) {
            sx += xa[i];
            sy += ya[i];
            sxx += xa[i] * xa[i];
            sxy += xa[i] * ya[i];
        }
        factor = n * sxx - sx * sx;
        if (factor == 0.0)
            return ERROR_INT("no solution found", procName, 1);
        factor = 1. / factor;

        *pa = factor * ((l_float32)n * sxy - sx * sy);
        *pb = factor * (sxx * sy - sx * sxy);
    }
    else if (pa) {
        for (i = 0; i < n; i++) {
            sxx += xa[i] * xa[i];
            sxy += xa[i] * ya[i];
        }
        if (sxx == 0.0)
            return ERROR_INT("no solution found", procName, 1);
        *pa = sxy / sxx;
    }
    else {
        for (i = 0; i < n; i++)
            sy += ya[i];
        *pb = sy / (l_float32)n;
    }

    if (pnafit) {
        *pnafit = numaCreate(n);
        for (i = 0; i < n; i++) {
            val = (*pa) * xa[i] + *pb;
            numaAddNumber(*pnafit, val);
        }
    }

    return 0;
}
