ptaGetArrays(PTA    *pta,
             NUMA  **pnax,
             NUMA  **pnay)
{
l_int32   i, n;
NUMA     *nax, *nay;

    PROCNAME("ptaGetArrays");

    if (!pta)
        return ERROR_INT("pta not defined", procName, 1);
    if (!pnax)
        return ERROR_INT("&nax not defined", procName, 1);
    if (!pnay)
        return ERROR_INT("&nay not defined", procName, 1);

    *pnax = *pnay = NULL;
    if ((n = ptaGetCount(pta)) == 0)
        return ERROR_INT("pta is empty", procName, 1);

    if ((nax = numaCreate(n)) == NULL)
        return ERROR_INT("nax not made", procName, 1);
    *pnax = nax;
    if ((nay = numaCreate(n)) == NULL)
        return ERROR_INT("nay not made", procName, 1);
    *pnay = nay;


    for (i = 0; i < n; i++) {
        nax->array[i] = pta->x[i];
        nay->array[i] = pta->y[i];
    }
    nax->n = nay->n = n;

    return 0;
}
