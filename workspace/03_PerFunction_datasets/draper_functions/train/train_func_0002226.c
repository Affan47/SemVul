pixConvert1To2Cmap(PIX  *pixs)
{
PIX      *pixd;
PIXCMAP  *cmap;

    PROCNAME("pixConvert1To2Cmap");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (PIX *)ERROR_PTR("pixs not 1 bpp", procName, NULL);

    if ((pixd = pixConvert1To2(NULL, pixs, 0, 1)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    cmap = pixcmapCreate(2);
    pixcmapAddColor(cmap, 255, 255, 255);
    pixcmapAddColor(cmap, 0, 0, 0);
    pixSetColormap(pixd, cmap);

    return pixd;
}
