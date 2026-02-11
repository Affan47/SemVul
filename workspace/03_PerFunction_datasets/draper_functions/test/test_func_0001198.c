fopenReadStream(const char  *filename)
{
char  *fname, *tail;
FILE  *fp;

    PROCNAME("fopenReadStream");

    if (!filename)
        return (FILE *)ERROR_PTR("filename not defined", procName, NULL);


    fname = genPathname(filename, NULL);
    fp = fopen(fname, "rb");
    FREE(fname);
    if (fp) return fp;


    splitPathAtDirectory(filename, NULL, &tail);
    fp = fopen(tail, "rb");
    FREE(tail);

    if (!fp)
        return (FILE *)ERROR_PTR("file not found", procName, NULL);
    return fp;
}
