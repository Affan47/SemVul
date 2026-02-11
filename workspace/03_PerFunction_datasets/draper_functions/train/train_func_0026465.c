pixEqualizeTRC(PIX       *pixd,
               PIX       *pixs,
               l_float32  fract,
	       l_int32    factor)
{
l_int32   d;
NUMA     *na;
PIX      *pixt, *pix8;
PIXCMAP  *cmap;

    PROCNAME("pixEqualizeTRC");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixd && (pixd != pixs))
        return (PIX *)ERROR_PTR("pixd not null or pixs", procName, pixd);
    cmap = pixGetColormap(pixs);
    d = pixGetDepth(pixs);
    if (d != 8 && d != 32 && !cmap)
        return (PIX *)ERROR_PTR("pixs not 8/32 bpp or cmapped", procName, NULL);
    if (fract < 0.0 || fract > 1.0)
        return (PIX *)ERROR_PTR("fract not in [0.0 ... 1.0]", procName, NULL);
    if (factor < 1)
        return (PIX *)ERROR_PTR("sampling factor < 1", procName, NULL);

    if (fract == 0.0)
        return pixCopy(pixd, pixs);


    if (cmap)
        pixt = pixRemoveColormap(pixs, REMOVE_CMAP_BASED_ON_SRC);
    else
        pixt = pixClone(pixs);


    pixd = pixCopy(pixd, pixt);
    pixDestroy(&pixt);

    d = pixGetDepth(pixd);
    if (d == 8) {
        na = numaEqualizeTRC(pixd, fract, factor);
        pixTRCMap(pixd, NULL, na);
        numaDestroy(&na);
    } else {
        pix8 = pixGetRGBComponent(pixd, COLOR_RED);
        na = numaEqualizeTRC(pix8, fract, factor);
        pixTRCMap(pix8, NULL, na);
        pixSetRGBComponent(pixd, pix8, COLOR_RED);
        numaDestroy(&na);
        pixDestroy(&pix8);
        pix8 = pixGetRGBComponent(pixd, COLOR_GREEN);
        na = numaEqualizeTRC(pix8, fract, factor);
        pixTRCMap(pix8, NULL, na);
        pixSetRGBComponent(pixd, pix8, COLOR_GREEN);
        numaDestroy(&na);
        pixDestroy(&pix8);
        pix8 = pixGetRGBComponent(pixd, COLOR_BLUE);
        na = numaEqualizeTRC(pix8, fract, factor);
        pixTRCMap(pix8, NULL, na);
        pixSetRGBComponent(pixd, pix8, COLOR_BLUE);
        numaDestroy(&na);
        pixDestroy(&pix8);
    }

    return pixd;
}
