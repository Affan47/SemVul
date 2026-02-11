pixScaleGray2xLIThresh(PIX     *pixs,
                       l_int32  thresh)
{
l_int32    i, ws, hs, hsm, wd, hd, wpls, wplb, wpld;
l_uint32  *datas, *datad, *lines, *lined, *lineb;
PIX       *pixd;

    PROCNAME("pixScaleGray2xLIThresh");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 8)
        return (PIX *)ERROR_PTR("pixs must be 8 bpp", procName, NULL);
    if (thresh < 0 || thresh > 256)
        return (PIX *)ERROR_PTR("thresh must be in [0, ... 256]",
            procName, NULL);
    if (pixGetColormap(pixs))
        L_WARNING("pixs has colormap", procName);

    pixGetDimensions(pixs, &ws, &hs, NULL);
    wd = 2 * ws;
    hd = 2 * hs;
    hsm = hs - 1;
    datas = pixGetData(pixs);
    wpls = pixGetWpl(pixs);


    wplb = (wd + 3) / 4;
    if ((lineb = (l_uint32 *)CALLOC(2 * wplb, sizeof(l_uint32))) == NULL)
        return (PIX *)ERROR_PTR("lineb not made", procName, NULL);


    if ((pixd = pixCreate(wd, hd, 1)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    pixCopyResolution(pixd, pixs);
    pixScaleResolution(pixd, 2.0, 2.0);
    wpld = pixGetWpl(pixd);
    datad = pixGetData(pixd);


    for (i = 0; i < hsm; i++) {
        lines = datas + i * wpls;
        lined = datad + 2 * i * wpld;
        scaleGray2xLILineLow(lineb, wplb, lines, ws, wpls, 0);
        thresholdToBinaryLineLow(lined, wd, lineb, 8, thresh);
        thresholdToBinaryLineLow(lined + wpld, wd, lineb + wplb, 8, thresh);
    }


    lines = datas + hsm * wpls;
    lined = datad + 2 * hsm * wpld;
    scaleGray2xLILineLow(lineb, wplb, lines, ws, wpls, 1);
    thresholdToBinaryLineLow(lined, wd, lineb, 8, thresh);
    thresholdToBinaryLineLow(lined + wpld, wd, lineb + wplb, 8, thresh);

    FREE(lineb);
    return pixd;
}
