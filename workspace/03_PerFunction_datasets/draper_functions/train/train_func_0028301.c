pixCompareTiled(PIX     *pix1,
                PIX     *pix2,
                l_int32  sx,
                l_int32  sy,
                l_int32  type,
                PIX    **ppixdiff)
{
l_int32    d1, d2, w, h;
PIX       *pixt, *pixr, *pixg, *pixb;
PIX       *pixrdiff, *pixgdiff, *pixbdiff;
PIXACC    *pixacc;

    PROCNAME("pixCompareTiled");

    if (!ppixdiff)
        return ERROR_INT("&pixdiff not defined", procName, 1);
    *ppixdiff = NULL;
    if (!pix1)
        return ERROR_INT("pix1 not defined", procName, 1);
    if (!pix2)
        return ERROR_INT("pix2 not defined", procName, 1);
    d1 = pixGetDepth(pix1);
    d2 = pixGetDepth(pix2);
    if (d1 != d2)
        return ERROR_INT("depths not equal", procName, 1);
    if (d1 != 8 && d1 != 32)
        return ERROR_INT("pix1 not 8 or 32 bpp", procName, 1);
    if (d2 != 8 && d2 != 32)
        return ERROR_INT("pix2 not 8 or 32 bpp", procName, 1);
    if (sx < 2 || sy < 2)
        return ERROR_INT("sx and sy not both > 1", procName, 1);
    if (type != L_MEAN_ABSVAL && type != L_ROOT_MEAN_SQUARE)
        return ERROR_INT("invalid type", procName, 1);

    pixt = pixAbsDifference(pix1, pix2);
    if (d1 == 8) {
        *ppixdiff = pixGetAverageTiled(pixt, sx, sy, type);
    } else {
        pixr = pixGetRGBComponent(pixt, COLOR_RED);
        pixg = pixGetRGBComponent(pixt, COLOR_GREEN);
        pixb = pixGetRGBComponent(pixt, COLOR_BLUE);
        pixrdiff = pixGetAverageTiled(pixr, sx, sy, type);
        pixgdiff = pixGetAverageTiled(pixg, sx, sy, type);
        pixbdiff = pixGetAverageTiled(pixb, sx, sy, type);
        pixGetDimensions(pixrdiff, &w, &h, NULL);
        pixacc = pixaccCreate(w, h, 0);
        pixaccAdd(pixacc, pixrdiff);
        pixaccAdd(pixacc, pixgdiff);
        pixaccAdd(pixacc, pixbdiff);
        pixaccMultConst(pixacc, 1. / 3.);
        *ppixdiff = pixaccFinal(pixacc, 8);
        pixDestroy(&pixr);
        pixDestroy(&pixg);
        pixDestroy(&pixb);
        pixDestroy(&pixrdiff);
        pixDestroy(&pixgdiff);
        pixDestroy(&pixbdiff);
        pixaccDestroy(&pixacc);
    }
    pixDestroy(&pixt);
    return 0;
}
