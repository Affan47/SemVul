genPathname(const char  *dir,
            const char  *fname)
{
char    *charbuf;
l_int32  dirlen, namelen, totlen;

    PROCNAME("genPathname");

    if (!dir)
        return (char *)ERROR_PTR("dir not defined", procName, NULL);
    if (!fname)
        return (char *)ERROR_PTR("fname not defined", procName, NULL);

    dirlen = strlen(dir);
    namelen = strlen(fname);
    totlen = dirlen + namelen + 20;
    if ((charbuf = (char *)CALLOC(totlen, sizeof(char))) == NULL)
        return (char *)ERROR_PTR("charbuf not made", procName, NULL);

#ifdef _WIN32
    if (stringFindSubstr(dir, "/", NULL) > 0) {
        char *tempname;
        tempname = stringReplaceEachSubstr(dir, "/", "\\", NULL);
        stringCopy(charbuf, tempname, strlen(tempname));
        FREE(tempname);
    }
    else {
        stringCopy(charbuf, dir, dirlen);
    }
#else
    stringCopy(charbuf, dir, dirlen);
#endif

    dirlen = strlen(charbuf);
    if (charbuf[dirlen - 1] != sepchar)
        charbuf[dirlen] = sepchar;
    strncat(charbuf, fname, namelen);
    return charbuf;
}
