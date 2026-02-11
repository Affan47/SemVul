pixColorizeGray(PIX      *pixs,
                l_uint32  color,
                l_int32   cmapflag)
{
l_int32    i, j, w, h, wplt, wpld, val8;
l_uint32  *datad, *datat, *lined, *linet, *tab;
PIX       *pixt, *pixd;
PIXCMAP   *cmap;

    PROCNAME("pixColorizeGray");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 8 && !pixGetColormap(pixs))
        return (PIX *)ERROR_PTR("pixs not 8 bpp or cmapped", procName, NULL);

    if (pixGetColormap(pixs))
        pixt = pixRemoveColormap(pixs, REMOVE_CMAP_TO_GRAYSCALE);
    else
        pixt = pixClone(pixs);

    cmap = pixcmapGrayToColor(color);
    if (cmapflag) {
        pixd = pixCopy(NULL, pixt);
        pixSetColormap(pixd, cmap);
        pixDestroy(&pixt);
        return pixd;
    }


    pixcmapToRGBTable(cmap, &tab, NULL);
    pixGetDimensions(pixt, &w, &h, NULL);
    pixd = pixCreate(w, h, 32);
    pixCopyResolution(pixd, pixs);
    datad = pixGetData(pixd);
    wpld = pixGetWpl(pixd);
    datat = pixGetData(pixt);
    wplt = pixGetWpl(pixt);
    for (i = 0; i < h; i++) {
        lined = datad + i * wpld;
        linet = datat + i * wplt;
        for (j = 0; j < w; j++) {
            val8 = GET_DATA_BYTE(linet, j);
            lined[j] = tab[val8];
        }
    }

    pixDestroy(&pixt);
    pixcmapDestroy(&cmap);
    FREE(tab);
    return pixd;
}
