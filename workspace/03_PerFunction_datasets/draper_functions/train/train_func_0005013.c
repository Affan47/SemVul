boxaaDisplay(BOXAA    *baa,
             l_int32   linewba,
             l_int32   linewb,
             l_uint32  colorba,
             l_uint32  colorb,
             l_int32   w,
             l_int32   h)
{
l_int32   i, j, n, m, rbox, gbox, bbox, rboxa, gboxa, bboxa;
BOX      *box;
BOXA     *boxa;
PIX      *pix;
PIXCMAP  *cmap;

    PROCNAME("boxaaDisplay");

    if (!baa)
        return (PIX *)ERROR_PTR("baa not defined", procName, NULL);
    if (w == 0 || h == 0)
        boxaaGetExtent(baa, &w, &h, NULL, NULL);

    pix = pixCreate(w, h, 8);
    cmap = pixcmapCreate(8);
    pixSetColormap(pix, cmap);
    extractRGBValues(colorb, &rbox, &gbox, &bbox);
    extractRGBValues(colorba, &rboxa, &gboxa, &bboxa);
    pixcmapAddColor(cmap, 255, 255, 255);
    pixcmapAddColor(cmap, rbox, gbox, bbox);
    pixcmapAddColor(cmap, rboxa, gboxa, bboxa);

    n = boxaaGetCount(baa);
    for (i = 0; i < n; i++) {
        boxa = boxaaGetBoxa(baa, i, L_CLONE);
        boxaGetExtent(boxa, NULL, NULL, &box);
        pixRenderBoxArb(pix, box, linewba, rboxa, gboxa, bboxa);
        boxDestroy(&box);
        m = boxaGetCount(boxa);
        for (j = 0; j < m; j++) {
            box = boxaGetBox(boxa, j, L_CLONE);
            pixRenderBoxArb(pix, box, linewb, rbox, gbox, bbox);
            boxDestroy(&box);
        }
        boxaDestroy(&boxa);
    }

    return pix;
}
