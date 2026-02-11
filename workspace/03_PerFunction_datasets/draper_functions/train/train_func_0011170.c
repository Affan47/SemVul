pixScaleGray2xLI(PIX  *pixs)
{
l_int32    ws, hs, wpls, wpld;
l_uint32  *datas, *datad;
PIX       *pixd;

    PROCNAME("pixScaleGray2xLI");

    if (!pixs || pixGetDepth(pixs) != 8 || pixGetColormap(pixs))
        return (PIX *)ERROR_PTR("pixs undefined, cmapped or not 8 bpp",
                                procName, NULL);

    pixGetDimensions(pixs, &ws, &hs, NULL);
    datas = pixGetData(pixs);
    wpls = pixGetWpl(pixs);
    if ((pixd = pixCreate(2 * ws, 2 * hs, 8)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    pixCopyResolution(pixd, pixs);
    pixScaleResolution(pixd, 2.0, 2.0);
    datad = pixGetData(pixd);
    wpld = pixGetWpl(pixd);
    scaleGray2xLILow(datad, wpld, datas, ws, hs, wpls);
    return pixd;
}
