pixaaDisplay(PIXAA   *paa,
             l_int32  w,
             l_int32  h)
{
l_int32  i, j, n, nbox, na, d, wmax, hmax, x, y, xb, yb, wb, hb;
BOXA    *boxa1;
BOXA    *boxa;
PIX     *pixt, *pixd;
PIXA    *pixa;

    PROCNAME("pixaaDisplay");

    if (!paa)
        return (PIX *)ERROR_PTR("paa not defined", procName, NULL);

    n = pixaaGetCount(paa, NULL);
    if (n == 0)
        return (PIX *)ERROR_PTR("no components", procName, NULL);


    boxa1 = pixaaGetBoxa(paa, L_CLONE);
    nbox = boxaGetCount(boxa1);
    if (w == 0 || h == 0) {
        if (nbox == n) {
            boxaGetExtent(boxa1, &w, &h, NULL);
        } else {
            wmax = hmax = 0;
            for (i = 0; i < n; i++) {
                pixa = pixaaGetPixa(paa, i, L_CLONE);
                boxa = pixaGetBoxa(pixa, L_CLONE);
                boxaGetExtent(boxa, &w, &h, NULL);
                wmax = L_MAX(wmax, w);
                hmax = L_MAX(hmax, h);
                pixaDestroy(&pixa);
                boxaDestroy(&boxa);
            }
            w = wmax;
            h = hmax;
        }
    }


    pixa = pixaaGetPixa(paa, 0, L_CLONE);
    pixt = pixaGetPix(pixa, 0, L_CLONE);
    d = pixGetDepth(pixt);
    pixaDestroy(&pixa);
    pixDestroy(&pixt);

    if ((pixd = pixCreate(w, h, d)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);

    x = y = 0;
    for (i = 0; i < n; i++) {
        pixa = pixaaGetPixa(paa, i, L_CLONE);
        if (nbox == n)
            boxaGetBoxGeometry(boxa1, i, &x, &y, NULL, NULL);
        na = pixaGetCount(pixa);
        for (j = 0; j < na; j++) {
            pixaGetBoxGeometry(pixa, j, &xb, &yb, &wb, &hb);
            pixt = pixaGetPix(pixa, j, L_CLONE);
            pixRasterop(pixd, x + xb, y + yb, wb, hb, PIX_PAINT, pixt, 0, 0);
            pixDestroy(&pixt);
        }
        pixaDestroy(&pixa);
    }
    boxaDestroy(&boxa1);

    return pixd;
}
