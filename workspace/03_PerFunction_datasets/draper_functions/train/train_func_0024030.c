getNextNonCommentLine(SARRAY  *sa,
                      l_int32  start,
                      l_int32 *pnext)
{
char    *str;
l_int32  i, n;

    PROCNAME("getNextNonCommentLine");

    if (!sa)
        return ERROR_INT("sa not defined", procName, 1);
    if (!pnext)
        return ERROR_INT("&pnext not defined", procName, 1);


    *pnext = -1;

    n = sarrayGetCount(sa);
    for (i = start; i < n; i++) {
        if ((str = sarrayGetString(sa, i, 0)) == NULL)
            return ERROR_INT("str not returned; shouldn't happen", procName, 1);
        if (str[0] != '#') {
            *pnext = i;
            return 0;
        }
    }

    return 0;
}
