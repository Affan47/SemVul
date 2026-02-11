bmfGetWordWidths(L_BMF       *bmf,
                 const char  *textstr,
                 SARRAY      *sa)
{
char    *wordstr;
l_int32  i, nwords, width;
NUMA    *na;

    PROCNAME("bmfGetWordWidths");

    if (!bmf)
        return (NUMA *)ERROR_PTR("bmf not defined", procName, NULL);
    if (!textstr)
        return (NUMA *)ERROR_PTR("teststr not defined", procName, NULL);
    if (!sa)
        return (NUMA *)ERROR_PTR("sa not defined", procName, NULL);

    nwords = sarrayGetCount(sa);
    if ((na = numaCreate(nwords)) == NULL)
        return (NUMA *)ERROR_PTR("na not made", procName, NULL);

    for (i = 0; i < nwords; i++) {
        wordstr = sarrayGetString(sa, i, 0);
        bmfGetStringWidth(bmf, wordstr, &width);
        numaAddNumber(na, width);
    }

    return na;
}
