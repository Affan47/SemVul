pixaBinSort(PIXA    *pixas,
            l_int32  sorttype,
            l_int32  sortorder,
            NUMA   **pnaindex,
            l_int32  copyflag)
{
l_int32  i, n, x, y, w, h;
BOXA    *boxa;
NUMA    *na, *naindex;
PIXA    *pixad;

    PROCNAME("pixaBinSort");

    if (pnaindex) *pnaindex = NULL;
    if (!pixas)
        return (PIXA *)ERROR_PTR("pixas not defined", procName, NULL);
    if (sorttype != L_SORT_BY_X && sorttype != L_SORT_BY_Y &&
        sorttype != L_SORT_BY_WIDTH && sorttype != L_SORT_BY_HEIGHT &&
        sorttype != L_SORT_BY_PERIMETER)
        return (PIXA *)ERROR_PTR("invalid sort type", procName, NULL);
    if (sortorder != L_SORT_INCREASING && sortorder != L_SORT_DECREASING)
        return (PIXA *)ERROR_PTR("invalid sort order", procName, NULL);
    if (copyflag != L_COPY && copyflag != L_CLONE)
        return (PIXA *)ERROR_PTR("invalid copy flag", procName, NULL);


    if ((boxa = pixas->boxa) == NULL)
        return (PIXA *)ERROR_PTR("boxa not found", procName, NULL);
    n = pixaGetCount(pixas);
    if (boxaGetCount(boxa) != n)
        return (PIXA *)ERROR_PTR("boxa and pixa counts differ", procName, NULL);


    if ((na = numaCreate(n)) == NULL)
        return (PIXA *)ERROR_PTR("na not made", procName, NULL);
    for (i = 0; i < n; i++) {
        boxaGetBoxGeometry(boxa, i, &x, &y, &w, &h);
        switch (sorttype)
        {
        case L_SORT_BY_X:
            numaAddNumber(na, x);
            break;
        case L_SORT_BY_Y:
            numaAddNumber(na, y);
            break;
        case L_SORT_BY_WIDTH:
            numaAddNumber(na, w);
            break;
        case L_SORT_BY_HEIGHT:
            numaAddNumber(na, h);
            break;
        case L_SORT_BY_PERIMETER:
            numaAddNumber(na, w + h);
            break;
        default:
            L_WARNING("invalid sort type\n", procName);
        }
    }


    if ((naindex = numaGetBinSortIndex(na, sortorder)) == NULL)
        return (PIXA *)ERROR_PTR("naindex not made", procName, NULL);


    if ((pixad = pixaSortByIndex(pixas, naindex, copyflag)) == NULL)
        return (PIXA *)ERROR_PTR("pixad not made", procName, NULL);

    if (pnaindex)
        *pnaindex = naindex;
    else
        numaDestroy(&naindex);
    numaDestroy(&na);
    return pixad;
}
