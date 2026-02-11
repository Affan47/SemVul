sarrayConvertWordsToLines(SARRAY  *sa,
                          l_int32  linesize)
{
char    *wd, *strl;
l_int32  n, i, len, totlen;
SARRAY  *sal, *saout;

    PROCNAME("sarrayConvertWordsToLines");

    if (!sa)
        return (SARRAY *)ERROR_PTR("sa not defined", procName, NULL);

    if ((saout = sarrayCreate(0)) == NULL)
        return (SARRAY *)ERROR_PTR("saout not defined", procName, NULL);

    n = sarrayGetCount(sa);
    totlen = 0;
    sal = NULL;
    for (i = 0; i < n; i++) {
        if (!sal) {
            if ((sal = sarrayCreate(0)) == NULL)
                return (SARRAY *)ERROR_PTR("sal not made", procName, NULL);
        }
        wd = sarrayGetString(sa, i, L_NOCOPY);
        len = strlen(wd);
        if (len == 0) {
            if (totlen > 0) {
                strl = sarrayToString(sal, 2);
                sarrayAddString(saout, strl, L_INSERT);
            }
            sarrayAddString(saout, "", L_COPY);
            sarrayDestroy(&sal);
            totlen = 0;
        }
        else if (totlen == 0 && len + 1 > linesize) {
            sarrayAddString(saout, wd, L_COPY);
        }
        else if (totlen + len + 1 > linesize) {
            strl = sarrayToString(sal, 2);
            sarrayAddString(saout, strl, L_INSERT);
            sarrayDestroy(&sal);
            if ((sal = sarrayCreate(0)) == NULL)
                return (SARRAY *)ERROR_PTR("sal not made", procName, NULL);
            sarrayAddString(sal, wd, L_COPY);
            totlen = len + 1;
        }
        else {
            sarrayAddString(sal, wd, L_COPY);
            totlen += len + 1;
        }
    }
    if (totlen > 0) {
        strl = sarrayToString(sal, 2);
        sarrayAddString(saout, strl, L_INSERT);
        sarrayDestroy(&sal);
    }

    return saout;

}
