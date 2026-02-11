skipToSemicolon(SARRAY   *sa,
                l_int32   start,
                l_int32   charindex,
                l_int32  *pnext)
{
char    *str;
l_int32  i, j, n, jstart, nchars, found;

    PROCNAME("skipToSemicolon");

    if (!sa)
        return ERROR_INT("sa not defined", procName, 1);
    if (!pnext)
        return ERROR_INT("&next not defined", procName, 1);

    *pnext = -1;
    n = sarrayGetCount(sa);
    found = FALSE;
    for (i = start; i < n; i++) {
        str = sarrayGetString(sa, i, 0);
        jstart = 0;
        if (i == start)
            jstart = charindex + 1;
        nchars = strlen(str);
        for (j = jstart; j < nchars; j++) {
            if (str[j] == ';') {
                found = TRUE;;
                break;
            }
        }
        if (found) {
            *pnext = i;
            return 0;
        }
    }

    return ERROR_INT("semicolon not found", procName, 1);
}
