sarraySelectByRange(SARRAY  *sain,
                    l_int32  first,
                    l_int32  last)
{
char    *str;
l_int32  n, i;
SARRAY  *saout;

    PROCNAME("sarraySelectByRange");

    if (!sain)
        return (SARRAY *)ERROR_PTR("sain not defined", procName, NULL);
    if (first < 0) first = 0;
    n = sarrayGetCount(sain);
    if (last <= 0) last = n - 1;
    if (last >= n) {
        L_WARNING("@last > n - 1; setting to n - 1", procName);
        last = n - 1;
    }
    if (first > last)
        return (SARRAY *)ERROR_PTR("first must be >= last", procName, NULL);

    saout = sarrayCreate(0);
    for (i = first; i <= last; i++) {
        str = sarrayGetString(sain, i, L_COPY);
        sarrayAddString(saout, str, L_INSERT);
    }

    return saout;
}
