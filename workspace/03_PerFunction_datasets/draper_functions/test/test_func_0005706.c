readHeaderTiff(const char *filename,
               l_int32     n,
               l_int32    *pwidth,
               l_int32    *pheight,
               l_int32    *pbps,
               l_int32    *pspp,
               l_int32    *pres,
               l_int32    *pcmap)
{
l_int32  ret;
FILE    *fp;

    PROCNAME("readHeaderTiff");

    if (!filename)
        return ERROR_INT("filename not defined", procName, 1);
    if (!pwidth || !pheight || !pbps || !pspp)
        return ERROR_INT("input ptr(s) not all defined", procName, 1);
    *pwidth = *pheight = *pbps = *pspp = 0;
    if (pres) *pres = 0;
    if (pcmap) *pcmap = 0;

    if ((fp = fopenReadStream(filename)) == NULL)
        return ERROR_INT("image file not found", procName, 1);
    ret = freadHeaderTiff(fp, n, pwidth, pheight, pbps, pspp, pres, pcmap);
    fclose(fp);
    return ret;
}
