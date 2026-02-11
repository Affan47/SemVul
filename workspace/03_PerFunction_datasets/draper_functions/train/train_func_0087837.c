Fsetcwd()
{
    int res, len;
    char pfad[MAXPFADLEN];
    char *pf1;

    if(*FLAGPTR(argStkPtr) != fSTRING) {
        error(setcwdsym,err_str,*argStkPtr);
        return brkerr();
    }
    len = *STRLENPTR(argStkPtr);
    if(len < MAXPFADLEN) {
        strncopy(pfad,STRINGPTR(argStkPtr),MAXPFADLEN);
#ifdef genUNiX
        if(strncmp(pfad,"~/",2) == 0) {
            expandtilde(pfad);
        }
#endif
        res = setworkdir(pfad);
    }
    else
        res = 0;
    if(res == 0)
        pf1 = "";
    else
        pf1 = getworkdir();
    return mkstr(pf1);
}
