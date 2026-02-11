boxaSelectWithIndicator(BOXA     *boxas,
                        NUMA     *na,
                        l_int32  *pchanged)
{
l_int32  i, n, ival, nsave;
BOX     *box;
BOXA    *boxad;

    PROCNAME("boxaSelectWithIndicator");

    if (!boxas)
        return (BOXA *)ERROR_PTR("boxas not defined", procName, NULL);
    if (!na)
        return (BOXA *)ERROR_PTR("na not defined", procName, NULL);

    nsave = 0;
    n = numaGetCount(na);
    for (i = 0; i < n; i++) {
        numaGetIValue(na, i, &ival);
        if (ival == 1) nsave++;
    }

    if (nsave == n) {
        if (pchanged) *pchanged = FALSE;
        return boxaCopy(boxas, L_CLONE);
    }
    if (pchanged) *pchanged = TRUE;
    boxad = boxaCreate(nsave);
    for (i = 0; i < n; i++) {
        numaGetIValue(na, i, &ival);
        if (ival == 0) continue;
        box = boxaGetBox(boxas, i, L_CLONE);
        boxaAddBox(boxad, box, L_INSERT);
    }

    return boxad;
}
