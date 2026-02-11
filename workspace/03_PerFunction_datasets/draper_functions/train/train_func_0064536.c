pixGrayQuantFromCmap(PIX      *pixs,
                     PIXCMAP  *cmap,
                     l_int32   mindepth)
{
l_int32    i, j, index, w, h, d, depth, wpls, wpld;
l_int32    hascolor, vals, vald;
l_int32   *tab;
l_uint32  *datas, *datad, *lines, *lined;
PIXCMAP   *cmapd;
PIX       *pixd;

    PROCNAME("pixGrayQuantFromCmap");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetColormap(pixs) != NULL) {
        L_WARNING("pixs already has a colormap; returning a copy", procName);
        return pixCopy(NULL, pixs);
    }
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8)
        return (PIX *)ERROR_PTR("pixs not 8 bpp", procName, NULL);
    if (!cmap)
        return (PIX *)ERROR_PTR("cmap not defined", procName, NULL);
    if (mindepth != 2 && mindepth != 4 && mindepth != 8)
        return (PIX *)ERROR_PTR("invalid mindepth", procName, NULL);


    pixcmapHasColor(cmap, &hascolor);
    if (hascolor) {
        L_WARNING("Converting colormap colors to gray", procName);
        cmapd = pixcmapColorToGray(cmap, 0.3, 0.5, 0.2);
    }
    else
        cmapd = pixcmapCopy(cmap);


    if ((tab = (l_int32 *)CALLOC(256, sizeof(l_int32))) == NULL)
        return (PIX *)ERROR_PTR("tab not made", procName, NULL);
    for (i = 0; i < 256; i++) {
        pixcmapGetNearestGrayIndex(cmapd, i, &index);
        tab[i] = index;
    }

    pixcmapGetMinDepth(cmap, &depth);
    depth = L_MAX(depth, mindepth);
    pixd = pixCreate(w, h, depth);
    pixSetColormap(pixd, cmapd);
    pixCopyResolution(pixd, pixs);
    pixCopyInputFormat(pixd, pixs);
    datas = pixGetData(pixs);
    datad = pixGetData(pixd);
    wpls = pixGetWpl(pixs);
    wpld = pixGetWpl(pixd);
    for (i = 0; i < h; i++) {
        lines = datas + i * wpls;
        lined = datad + i * wpld;
        for (j = 0; j < w; j++) {
            vals = GET_DATA_BYTE(lines, j);
            vald = tab[vals];
            if (depth == 2)
                SET_DATA_DIBIT(lined, j, vald);
            else if (depth == 4)
                SET_DATA_QBIT(lined, j, vald);
            else
                SET_DATA_BYTE(lined, j, vald);
        }
    }

    FREE(tab);
    return pixd;
}
