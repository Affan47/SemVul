pixPaintBoxaRandom(PIX   *pixs,
                   BOXA  *boxa)
{
l_int32   i, n, d, rval, gval, bval, index;
l_uint32  val;
BOX      *box;
PIX      *pixd;
PIXCMAP  *cmap;

    PROCNAME("pixPaintBoxaRandom");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (!boxa)
        return (PIX *)ERROR_PTR("boxa not defined", procName, NULL);

    if ((n = boxaGetCount(boxa)) == 0) {
        L_WARNING("no boxes to paint; returning a copy\n", procName);
        return pixCopy(NULL, pixs);
    }

    if (pixGetDepth(pixs) == 1)
        pixd = pixConvert1To8(NULL, pixs, 255, 0);
    else
        pixd = pixConvertTo32(pixs);
    if (!pixd)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);

    cmap = pixcmapCreateRandom(8, 1, 1);
    d = pixGetDepth(pixd);
    if (d == 8)
        pixSetColormap(pixd, cmap);

    for (i = 0; i < n; i++) {
        box = boxaGetBox(boxa, i, L_CLONE);
        index = 1 + (i % 254);
        if (d == 8) {
            pixSetInRectArbitrary(pixd, box, index);
        } else {
            pixcmapGetColor(cmap, index, &rval, &gval, &bval);
            composeRGBPixel(rval, gval, bval, &val);
            pixSetInRectArbitrary(pixd, box, val);
        }
        boxDestroy(&box);
    }

    if (d == 32)
        pixcmapDestroy(&cmap);
    return pixd;
}
