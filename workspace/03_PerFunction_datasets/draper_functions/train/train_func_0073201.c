l_binaryReadSelect(const char  *filename,
                   size_t       start,
                   size_t       nbytes,
                   size_t      *pnread)
{
l_uint8  *data;
FILE     *fp;

    PROCNAME("l_binaryReadSelect");

    if (!pnread)
        return (l_uint8 *)ERROR_PTR("pnread not defined", procName, NULL);
    *pnread = 0;
    if (!filename)
        return (l_uint8 *)ERROR_PTR("filename not defined", procName, NULL);

    if ((fp = fopenReadStream(filename)) == NULL)
        return (l_uint8 *)ERROR_PTR("file stream not opened", procName, NULL);
    data = l_binaryReadSelectStream(fp, start, nbytes, pnread);
    fclose(fp);
    return data;
}
