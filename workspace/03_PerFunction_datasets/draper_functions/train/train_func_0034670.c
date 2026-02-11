pixGenerateG4Data(PIX     *pixs,
                  l_int32  ascii85flag)
{
char         *tname;
L_COMP_DATA  *cid;

    PROCNAME("pixGenerateG4Data");

    if (!pixs)
        return (L_COMP_DATA *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (L_COMP_DATA *)ERROR_PTR("pixs not 1 bpp", procName, NULL);


    tname = genTempFilename("/tmp", "temp.tif", 1, 1);
    pixWrite(tname, pixs, IFF_TIFF_G4);

    cid = l_generateG4Data(tname, ascii85flag);
    lept_rm(NULL, tname);
    lept_free(tname);
    return cid;
}
