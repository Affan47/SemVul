skipToMatchingBrace(SARRAY   *sa,
                    l_int32   start,
                    l_int32   lbindex,
                    l_int32  *pstop,
                    l_int32  *prbindex)
{
char    *str;
l_int32  i, j, jstart, n, sumbrace, found, instring, nchars;

    PROCNAME("skipToMatchingBrace");

    if (!sa)
        return ERROR_INT("sa not defined", procName, 1);
    if (!pstop)
        return ERROR_INT("&stop not defined", procName, 1);
    if (!prbindex)
        return ERROR_INT("&rbindex not defined", procName, 1);

    instring = 0;
    *pstop = -1;
    n = sarrayGetCount(sa);
    sumbrace = 1;
    found = FALSE;
    for (i = start; i < n; i++) {
        str = sarrayGetString(sa, i, 0);
        jstart = 0;
        if (i == start)
            jstart = lbindex + 1;
        nchars = strlen(str);
        for (j = jstart; j < nchars; j++) {


            if (j == jstart && str[j] == '\"')
                instring = 1 - instring;
            if (j > jstart && str[j] == '\"' && str[j-1] != '\\')
                instring = 1 - instring;


            if (str[j] == '{' && str[j+1] != '\'' && !instring) {
                sumbrace++;
            } else if (str[j] == '}' && str[j+1] != '\'' && !instring) {
                sumbrace--;
                if (sumbrace == 0) {
                    found = TRUE;
                    *prbindex = j;
                    break;
                }
            }
        }
        if (found) {
            *pstop = i;
            return 0;
        }
    }

    return ERROR_INT("matching right brace not found", procName, 1);
}
