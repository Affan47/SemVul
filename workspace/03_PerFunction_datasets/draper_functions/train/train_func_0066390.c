ptraJoin(PTRA  *pa1,
         PTRA  *pa2)
{
l_int32  i, n;
void    *item;

    PROCNAME("ptraJoin");

    if (!pa1)
        return ERROR_INT("pa1 not defined", procName, 1);
    if (!pa2)
        return 0;

    ptraGetMaxIndex(pa2, &n);
    for (i = 0; i < n; i++) {
        item = ptraRemove(pa2, i, L_NO_COMPACTION);
        ptraAdd(pa1, item);
    }

    ptraGetMaxIndex(pa2, &n);
    fprintf(stderr, "n = %d\n", n);

    return 0;
}
