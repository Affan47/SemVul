pixaDisplayOnLattice(PIXA    *pixa,
                     l_int32  xspace,
                     l_int32  yspace)
{
l_int32  n, nw, nh, w, h, d, wt, ht;
l_int32  index, i, j;
PIX     *pixt, *pixd;

    PROCNAME("pixaDisplayOnLattice");

    if (!pixa)
        return (PIX *)ERROR_PTR("pixa not defined", procName, NULL);

    if ((n = pixaGetCount(pixa)) == 0)
        return (PIX *)ERROR_PTR("no components", procName, NULL);
    nw = (l_int32)sqrt((l_float64)n);
    nh = (n + nw - 1) / nw;
    w = xspace * nw;
    h = yspace * nh;


    pixt = pixaGetPix(pixa, 0, L_CLONE);
    d = pixGetDepth(pixt);
    pixDestroy(&pixt);

    if ((pixd = pixCreate(w, h, d)) == NULL)
        return (PIX *)ERROR_PTR("pixd not made", procName, NULL);

    index = 0;
    for (i = 0; i < nh; i++) {
        for (j = 0; j < nw && index < n; j++, index++) {
            pixt = pixaGetPix(pixa, index, L_CLONE);
            pixGetDimensions(pixt, &wt, &ht, NULL);
            if (wt > xspace || ht > yspace) {
                fprintf(stderr, "pix(%d) omitted; size %dx%d\n", index, wt, ht);
                pixDestroy(&pixt);
                continue;
            }
            pixRasterop(pixd, j * xspace, i * yspace, wt, ht,
                        PIX_PAINT, pixt, 0, 0);
            pixDestroy(&pixt);
        }
    }

    return pixd;
}
