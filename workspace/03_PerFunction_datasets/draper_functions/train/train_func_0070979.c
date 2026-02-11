ptaGetRange(PTA        *pta,
            l_float32  *pminx,
            l_float32  *pmaxx,
            l_float32  *pminy,
            l_float32  *pmaxy)
{
l_int32    n, i;
l_float32  x, y, minx, maxx, miny, maxy;

    PROCNAME("ptaGetRange");

    if (!pminx && !pmaxx && !pminy && !pmaxy)
        return ERROR_INT("no output requested", procName, 1);
    if (pminx) *pminx = 0;
    if (pmaxx) *pmaxx = 0;
    if (pminy) *pminy = 0;
    if (pmaxy) *pmaxy = 0;
    if (!pta)
        return ERROR_INT("pta not defined", procName, 1);
    if ((n = ptaGetCount(pta)) == 0)
        return ERROR_INT("no points in pta", procName, 1);

    ptaGetPt(pta, 0, &x, &y);
    minx = x;
    maxx = x;
    miny = y;
    maxy = y;
    for (i = 1; i < n; i++) {
        ptaGetPt(pta, i, &x, &y);
        if (x < minx) minx = x;
        if (x > maxx) maxx = x;
        if (y < miny) miny = y;
        if (y > maxy) maxy = y;
    }
    if (pminx) *pminx = minx;
    if (pmaxx) *pmaxx = maxx;
    if (pminy) *pminy = miny;
    if (pmaxy) *pmaxy = maxy;
    return 0;
}
