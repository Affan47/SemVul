pixErode(PIX  *pixd,
         PIX  *pixs,
         SEL  *sel)
{
l_int32  i, j, w, h, sx, sy, cx, cy, seldata;
l_int32  xp, yp, xn, yn;
PIX     *pixt;

    PROCNAME("pixErode");

    if ((pixd = processMorphArgs1(pixd, pixs, sel, &pixt)) == NULL)
        return (PIX *)ERROR_PTR("processMorphArgs1 failed", procName, pixd);

    pixGetDimensions(pixs, &w, &h, NULL);
    selGetParameters(sel, &sy, &sx, &cy, &cx);
    pixSetAll(pixd);
    for (i = 0; i < sy; i++) {
        for (j = 0; j < sx; j++) {
            seldata = sel->data[i][j];
            if (seldata == 1) {
                    pixRasterop(pixd, cx - j, cy - i, w, h, PIX_SRC & PIX_DST,
                                pixt, 0, 0);
            }
        }
    }


    if (MORPH_BC == ASYMMETRIC_MORPH_BC) {
        selFindMaxTranslations(sel, &xp, &yp, &xn, &yn);
        if (xp > 0)
            pixRasterop(pixd, 0, 0, xp, h, PIX_CLR, NULL, 0, 0);
        if (xn > 0)
            pixRasterop(pixd, w - xn, 0, xn, h, PIX_CLR, NULL, 0, 0);
        if (yp > 0)
            pixRasterop(pixd, 0, 0, w, yp, PIX_CLR, NULL, 0, 0);
        if (yn > 0)
            pixRasterop(pixd, 0, h - yn, w, yn, PIX_CLR, NULL, 0, 0);
    }

    pixDestroy(&pixt);
    return pixd;
}
