pathJoin(const char  *dir,
         const char  *fname)
{
char     *slash = (char *)"/";
char     *str, *dest;
l_int32   i, n1, n2, emptydir;
size_t    size;
SARRAY   *sa1, *sa2;
L_BYTEA  *ba;

    if (!dir && !fname)
        return stringNew("");

    sa1 = sarrayCreate(0);
    sa2 = sarrayCreate(0);
    ba = l_byteaCreate(4);


    if (dir && strlen(dir) > 0) {
        if (dir[0] == '/')
            l_byteaAppendString(ba, slash);
        sarraySplitString(sa1, dir, "/");
        n1 = sarrayGetCount(sa1);
        for (i = 0; i < n1; i++) {
            str = sarrayGetString(sa1, i, L_NOCOPY);
            l_byteaAppendString(ba, str);
            l_byteaAppendString(ba, slash);
        }
    }


    emptydir = dir && strlen(dir) == 0;
    if ((!dir || emptydir) && fname && strlen(fname) > 0 && fname[0] == '/')
        l_byteaAppendString(ba, slash);


    if (fname && strlen(fname) > 0) {
        sarraySplitString(sa2, fname, "/");
        n2 = sarrayGetCount(sa2);
        for (i = 0; i < n2; i++) {
            str = sarrayGetString(sa2, i, L_NOCOPY);
            l_byteaAppendString(ba, str);
            l_byteaAppendString(ba, slash);
        }
    }


    dest = (char *)l_byteaCopyData(ba, &size);
    if (size > 1 && dest[size - 1] == '/')
        dest[size - 1] = '\0';

    sarrayDestroy(&sa1);
    sarrayDestroy(&sa2);
    l_byteaDestroy(&ba);
    return dest;
}
