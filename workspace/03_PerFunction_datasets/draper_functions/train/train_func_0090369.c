pixGenerateJpegData(PIX     *pixs,
                    l_int32  ascii85flag,
                    l_int32  quality)
{
l_int32       d;
char         *fname;
L_COMP_DATA  *cid;

    PROCNAME("pixGenerateJpegData");

    if (!pixs)
        return (L_COMP_DATA *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetColormap(pixs))
        return (L_COMP_DATA *)ERROR_PTR("pixs has colormap", procName, NULL);
    d = pixGetDepth(pixs);
    if (d != 8 && d != 32)
        return (L_COMP_DATA *)ERROR_PTR("pixs not 8 or 32 bpp", procName, NULL);


    fname = genTempFilename("/tmp", "temp.jpg", 1, 1);
    pixWriteJpeg(fname, pixs, quality, 0);

    cid = l_generateJpegData(fname, ascii85flag);
    lept_rm(NULL, fname);
    lept_free(fname);
    return cid;
}
