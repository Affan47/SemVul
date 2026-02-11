pixAddAlphaTo1bpp(PIX  *pixd,
                  PIX  *pixs)
{
PIXCMAP  *cmap;

    PROCNAME("pixAddAlphaTo1bpp");

    if (!pixs || (pixGetDepth(pixs) != 1))
        return (PIX *)ERROR_PTR("pixs undefined or not 1 bpp", procName, NULL);
    if (pixd && (pixd != pixs))
        return (PIX *)ERROR_PTR("pixd defined but != pixs", procName, NULL);

    pixd = pixInvert(pixd, pixs);
    cmap = pixcmapCreate(1);
    pixSetColormap(pixd, cmap);
    pixcmapAddRGBA(cmap, 0, 0, 0, 255);
    pixcmapAddRGBA(cmap, 255, 255, 255, 0);
    return pixd;
}
