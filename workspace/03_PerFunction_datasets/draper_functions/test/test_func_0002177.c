DoFindMyself(char *myself, char **mypath, char **gappath)
{
    char *tmppath;
    char *p;


    *mypath = realpath(myself,NULL);
    if (*mypath == NULL) {
        printf("Could not determine my own path, giving up.\n");
        exit(-1);
    }
    tmppath = NULL;
    StrAppend(&tmppath,*mypath);
    p = tmppath+strlen(tmppath);
    while (*p != '/') p--;
    *p = 0;
    StrAppend(&tmppath,"/../..");
    *gappath = realpath(tmppath,NULL);
    if (*gappath == NULL) {
        printf("Could not determine GAP path, giving up.\n");
        exit(-2);
    }
    free(tmppath);
}
