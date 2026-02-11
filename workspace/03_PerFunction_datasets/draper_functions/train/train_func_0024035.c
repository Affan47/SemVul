pixThresholdToBinary(PIX     *pixs,
                     l_int32  thresh)
{
l_int32    d, w, h, wplt, wpld;
l_uint32  *datat, *datad;
PIX       *pixt, *pixd;

    PROCNAME("pixThresholdToBinary");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 4 && d != 8)
        return (PIX *)ERROR_PTR("pixs must be 4 or 8 bpp", procName, NULL);
    if (thresh < 0)
        return (PIX *)ERROR_PTR("thresh must be non-negative", procName, NULL);
    if (d == 4 && thresh > 16)
        return (PIX *)ERROR_PTR("4 bpp thresh not in {0-16}", procName, NULL);
    if (d == 8 && thresh > 256)
        return (PIX *)ERROR_PTR("8 bpp thresh not in {0-256}", procName, NULL);

    if ((pixd = pixCreate(w, h, 1)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    pixCopyResolution(pixd, pixs);
    datad = pixGetData(pixd);
    wpld = pixGetWpl(pixd);


    pixt = pixRemoveColormap(pixs, REMOVE_CMAP_TO_GRAYSCALE);
    datat = pixGetData(pixt);
    wplt = pixGetWpl(pixt);
    if (pixGetColormap(pixs) && d == 4) {
        d = 8;
        thresh *= 16;
    }

    thresholdToBinaryLow(datad, w, h, wpld, datat, d, wplt, thresh);
    pixDestroy(&pixt);
    return pixd;
}
