numaGetEdgeValues(NUMA    *na,
                  l_int32  edge,
                  l_int32 *pstart,
                  l_int32 *pend,
                  l_int32 *psign)
{
l_int32  n, nedges;

    PROCNAME("numaGetEdgeValues");

    if (!na)
        return ERROR_INT("na not defined", procName, 1);
    n = numaGetCount(na);
    if (n % 3 != 1)
        return ERROR_INT("n % 3 is not 1", procName, 1);
    nedges = (n - 1) / 3;
    if (edge < 0 || edge >= nedges)
        return ERROR_INT("invalid edge", procName, 1);

    if (pstart) numaGetIValue(na, 3 * edge + 1, pstart);
    if (pend) numaGetIValue(na, 3 * edge + 2, pend);
    if (psign) numaGetIValue(na, 3 * edge + 3, psign);
    return 0;
}
