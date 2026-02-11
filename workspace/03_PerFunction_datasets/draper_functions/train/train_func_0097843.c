sycheck_cmtab(const char *cmtab)

{   struct stat sfile;
    char *dirname=NULL;
    int pos, eflag=ERR_NOERROR;


    pos = (int)strlen(cmtab);
    dirname = (char*)malloc((size_t)(pos + 1));
    for ( ; pos>0 && cmtab[pos-1] != '/'; --pos) dirname[pos] = '\0';
    while (--pos >= 0) dirname[pos] = cmtab[pos];
    eflag = sycheck_directory(dirname);
    if (eflag != ERR_NOERROR) goto bail_out;

    if (stat(cmtab,&sfile) != 0) {
        fprintf(stderr, "Cannot open \"%s\"\n", cmtab);
        eflag = ERR_INSECURE;
        goto bail_out;
    }


    if (sfile.st_uid != (uid_t)0) {
        fprintf(stderr, "\"%s\" must be owned by root\n", cmtab);
        eflag = ERR_INSECURE;
        goto bail_out;
    }


    if (!S_ISREG(sfile.st_mode) || (sfile.st_mode & S_IWOTH) != 0) {
        fprintf(stderr, "Lax permissions on \"%s\"\n", cmtab);
        eflag = ERR_INSECURE;
        goto bail_out;
    }

  bail_out:

    if (dirname != NULL) free((void*)dirname);

    return eflag;
}
