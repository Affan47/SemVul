pixaaWrite(const char  *filename,
           PIXAA       *pixaa)
{
FILE  *fp;

    PROCNAME("pixaaWrite");

#if !HAVE_LIBPNG
    return ERROR_INT("no libpng: can't read data", procName, 1);
#endif

    if (!filename)
        return ERROR_INT("filename not defined", procName, 1);
    if (!pixaa)
        return ERROR_INT("pixaa not defined", procName, 1);

    if ((fp = fopen(filename, "wb")) == NULL)
        return ERROR_INT("stream not opened", procName, 1);
    if (pixaaWriteStream(fp, pixaa))
        return ERROR_INT("pixaa not written to stream", procName, 1);
    fclose(fp);

    return 0;
}
