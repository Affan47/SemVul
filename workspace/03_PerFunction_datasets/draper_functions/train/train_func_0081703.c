strtokSafe(char        *cstr,
           const char  *seps,
           char       **psaveptr)
{
char     nextc;
char    *start, *substr;
l_int32  istart, i, j, nchars;

    PROCNAME("strtokSafe");

    if (!seps)
        return (char *)ERROR_PTR("seps not defined", procName, NULL);
    if (!psaveptr)
        return (char *)ERROR_PTR("&saveptr not defined", procName, NULL);

    if (!cstr)
        start = *psaveptr;
    else
        start = cstr;
    if (!start)
        return NULL;


    istart = 0;
    if (cstr) {
        for (istart = 0;; istart++) {
            if ((nextc = start[istart]) == '\0') {
                *psaveptr = NULL;
                return NULL;
            }
            if (!strchr(seps, nextc))
                break;
        }
    }


    for (i = istart;; i++) {
        if ((nextc = start[i]) == '\0')
            break;
        if (strchr(seps, nextc))
            break;
    }


    nchars = i - istart;
    substr = (char *)CALLOC(nchars + 1, sizeof(char));
    strncpy(substr, start + istart, nchars);


    for (j = i;; j++) {
        if ((nextc = start[j]) == '\0') {
            *psaveptr = NULL;
            break;
        }
        if (!strchr(seps, nextc)) {
            *psaveptr = start + j;
                break;
        }
    }

    return substr;
}
