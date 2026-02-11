pixCopyRGBComponent(PIX     *pixd,
                    PIX     *pixs,
                    l_int32  comp)
{
l_int32    i, j, w, h, ws, hs, wd, hd, val;
l_int32    wpls, wpld;
l_uint32  *lines, *lined;
l_uint32  *datas, *datad;

    PROCNAME("pixCopyRGBComponent");

    if (!pixd && pixGetDepth(pixd) != 32)
        return ERROR_INT("pixd not defined or not 32 bpp", procName, 1);
    if (!pixs && pixGetDepth(pixs) != 32)
        return ERROR_INT("pixs not defined or not 32 bpp", procName, 1);
    if (comp != COLOR_RED && comp != COLOR_GREEN &&
        comp != COLOR_BLUE && comp != L_ALPHA_CHANNEL)
        return ERROR_INT("invalid component", procName, 1);
    pixGetDimensions(pixs, &ws, &hs, NULL);
    pixGetDimensions(pixd, &wd, &hd, NULL);
    if (ws != wd || hs != hd)
        L_WARNING("images sizes not equal\n", procName);
    w = L_MIN(ws, wd);
    h = L_MIN(hs, hd);
    if (comp == L_ALPHA_CHANNEL)
        pixSetSpp(pixd, 4);
    wpls = pixGetWpl(pixs);
    wpld = pixGetWpl(pixd);
    datas = pixGetData(pixs);
    datad = pixGetData(pixd);
    for (i = 0; i < h; i++) {
        lines = datas + i * wpls;
        lined = datad + i * wpld;
        for (j = 0; j < w; j++) {
            val = GET_DATA_BYTE(lines + j, comp);
            SET_DATA_BYTE(lined + j, comp, val);
        }
    }
    return 0;
}
