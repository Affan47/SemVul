numaGetMin(NUMA       *na,
           l_float32  *pminval,
           l_int32    *piminloc)
{
l_int32    i, n, iminloc;
l_float32  val, minval;

    PROCNAME("numaGetMin");

    if (!na)
        return ERROR_INT("na not defined", procName, 1);
    if (!pminval && !piminloc)
        return ERROR_INT("nothing to don", procName, 1);
    if (pminval) *pminval = 0.0;
    if (piminloc) *piminloc = 0;

    minval = +1000000000.;
    iminloc = 0;
    n = numaGetCount(na);
    for (i = 0; i < n; i++) {
        numaGetFValue(na, i, &val);
        if (val < minval) {
            minval = val;
            iminloc = i;
        }
    }

    if (pminval) *pminval = minval;
    if (piminloc) *piminloc = iminloc;
    return 0;
}
