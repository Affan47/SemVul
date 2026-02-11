pixPrintStreamInfo(FILE        *fp,
                   PIX         *pix,
                   const char  *text)
{
l_int32   informat;
PIXCMAP  *cmap;

    PROCNAME("pixPrintStreamInfo");

    if (!fp)
        return ERROR_INT("fp not defined", procName, 1);
    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);

    if (text)
        fprintf(fp, "  Pix Info for %s:\n", text);
    fprintf(fp, "    width = %d, height = %d, depth = %d\n",
               pixGetWidth(pix), pixGetHeight(pix), pixGetDepth(pix));
    fprintf(fp, "    wpl = %d, data = %p, refcount = %d\n",
               pixGetWpl(pix), pixGetData(pix), pixGetRefcount(pix));
    if ((cmap = pixGetColormap(pix)) != NULL)
        pixcmapWriteStream(fp, cmap);
    else
        fprintf(fp, "    no colormap\n");
    informat = pixGetInputFormat(pix);
    fprintf(fp, "    input format: %d (%s)\n", informat,
            ImageFileFormatExtensions[informat]);

    return 0;
}
