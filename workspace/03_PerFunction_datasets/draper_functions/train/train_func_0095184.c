genPathname(const char  *dir,
            const char  *fname)
{
char    *cdir, *pathout;
l_int32  dirlen, namelen, size;

    PROCNAME("genPathname");

    if (!dir && !fname)
        return (char *)ERROR_PTR("no input", procName, NULL);


    if (!dir || dir[0] == '\0') {
        if ((cdir = getcwd(NULL, 0)) == NULL)
            return (char *)ERROR_PTR("no current dir found", procName, NULL);
    } else {
        cdir = stringNew(dir);
    }


    convertSepCharsInPath(cdir, UNIX_PATH_SEPCHAR);
    dirlen = strlen(cdir);
    if (cdir[dirlen - 1] == '/' && dirlen != 1) {
        cdir[dirlen - 1] = '\0';
        dirlen--;
    }

    namelen = (fname) ? strlen(fname) : 0;
    size = dirlen + namelen + 256;
    if ((pathout = (char *)CALLOC(size, sizeof(char))) == NULL)
        return (char *)ERROR_PTR("pathout not made", procName, NULL);


#ifdef _WIN32
    if (strncmp(cdir, "/tmp", 4) != 0) {
        stringCopy(pathout, cdir, dirlen);
    } else {

        char  dirt[MAX_PATH];
        GetTempPath(sizeof(dirt), dirt);
        stringCopy(pathout, dirt, strlen(dirt) - 1);


        if (dirlen > 4)
            stringCat(pathout, size, cdir + 4);
    }
#else
    stringCopy(pathout, cdir, dirlen);
#endif


    if (fname && strlen(fname) > 0) {
        dirlen = strlen(pathout);
        pathout[dirlen] = '/';
        strncat(pathout, fname, namelen);
    }

    FREE(cdir);
    return pathout;
}
