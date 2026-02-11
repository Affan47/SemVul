pixDrawBoxa(PIX      *pixs,
            BOXA     *boxa,
            l_int32   width,
            l_uint32  val)
{
l_int32   rval, gval, bval, newindex;
l_int32   mapvacancy;
PIX      *pixd;
PIXCMAP  *cmap;

    PROCNAME("pixDrawBoxa");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!boxa)
        return (PIX *)ERROR_PTR("boxa not defined", procName, NULL);
    if (width < 1)
        return (PIX *)ERROR_PTR("width must be >= 1", procName, NULL);

    if (boxaGetCount(boxa) == 0) {
        L_WARNING("no boxes to draw; returning a copy", procName);
        return pixCopy(NULL, pixs);
    }

    mapvacancy = FALSE;
    if ((cmap = pixGetColormap(pixs)) != NULL) {
        if (pixcmapGetCount(cmap) < 256)
            mapvacancy = TRUE;
    }
    if (pixGetDepth(pixs) == 1 || mapvacancy)
        pixd = pixConvertTo8(pixs, TRUE);
    else
        pixd = pixConvertTo32(pixs);
    if (!pixd)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);

    extractRGBValues(val, &rval, &gval, &bval);
    if (pixGetDepth(pixd) == 8) {
        cmap = pixGetColormap(pixd);
        pixcmapAddNewColor(cmap, rval, gval, bval, &newindex);
    }

    pixRenderBoxaArb(pixd, boxa, width, rval, gval, bval);
    return pixd;
}
