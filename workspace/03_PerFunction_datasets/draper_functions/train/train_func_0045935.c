pixaDisplayOnColor(PIXA     *pixa,
                   l_int32   w,
                   l_int32   h,
                   l_uint32  bgcolor)
{
l_int32  i, n, xb, yb, wb, hb, hascmap, maxdepth, same;
BOXA    *boxa;
PIX     *pixt1, *pixt2, *pixd;
PIXA    *pixat;

    PROCNAME("pixaDisplayOnColor");

    if (!pixa)
        return (PIX *)ERROR_PTR("pixa not defined", procName, NULL);
    if ((n = pixaGetCount(pixa)) == 0)
        return (PIX *)ERROR_PTR("no components", procName, NULL);


    if (w == 0 || h == 0) {
        boxa = pixaGetBoxa(pixa, L_CLONE);
        boxaGetExtent(boxa, &w, &h, NULL);
        boxaDestroy(&boxa);
    }


    pixaAnyColormaps(pixa, &hascmap);
    pixaGetDepthInfo(pixa, &maxdepth, &same);
    if (hascmap || !same) {
        maxdepth = 32;
        pixat = pixaCreate(n);
        for (i = 0; i < n; i++) {
            pixt1 = pixaGetPix(pixa, i, L_CLONE);
            pixt2 = pixConvertTo32(pixt1);
            pixaAddPix(pixat, pixt2, L_INSERT);
            pixDestroy(&pixt1);
        }
    } else {
        pixat = pixaCopy(pixa, L_CLONE);
    }


    if ((pixd = pixCreate(w, h, maxdepth)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);
    if ((maxdepth == 1 && bgcolor > 0) ||
        (maxdepth == 2 && bgcolor >= 0x3) ||
        (maxdepth == 4 && bgcolor >= 0xf) ||
        (maxdepth == 8 && bgcolor >= 0xff) ||
        (maxdepth == 16 && bgcolor >= 0xffff) ||
        (maxdepth == 32 && bgcolor >= 0xffffff00)) {
        pixSetAll(pixd);
    } else if (bgcolor > 0) {
        pixSetAllArbitrary(pixd, bgcolor);
    }


    for (i = 0; i < n; i++) {
        if (pixaGetBoxGeometry(pixat, i, &xb, &yb, &wb, &hb)) {
            L_WARNING("no box found!\n", procName);
            continue;
        }
        pixt1 = pixaGetPix(pixat, i, L_CLONE);
        pixRasterop(pixd, xb, yb, wb, hb, PIX_SRC, pixt1, 0, 0);
        pixDestroy(&pixt1);
    }

    pixaDestroy(&pixat);
    return pixd;
}
