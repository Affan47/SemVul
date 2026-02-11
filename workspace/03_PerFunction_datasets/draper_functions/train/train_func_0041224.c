pixaMorphSequenceByRegion(PIX         *pixs,
                          PIXA        *pixam,
                          const char  *sequence,
                          l_int32      minw,
                          l_int32      minh)
{
l_int32  n, i, w, h, d;
BOX     *box;
PIX     *pixt1, *pixt2, *pixt3;
PIXA    *pixad;

    PROCNAME("pixaMorphSequenceByRegion");

    if (!pixs)
        return (PIXA *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 1)
        return (PIXA *)ERROR_PTR("pixs not 1 bpp", procName, NULL);
    if (!pixam)
        return (PIXA *)ERROR_PTR("pixam not defined", procName, NULL);
    pixaGetPixDimensions(pixam, 0, NULL, NULL, &d);
    if (d != 1)
        return (PIXA *)ERROR_PTR("mask depth not 1 bpp", procName, NULL);
    if ((n = pixaGetCount(pixam)) == 0)
        return (PIXA *)ERROR_PTR("no regions specified", procName, NULL);
    if (n != pixaGetBoxaCount(pixam))
        L_WARNING("boxa size != n", procName);
    if (!sequence)
        return (PIXA *)ERROR_PTR("sequence not defined", procName, NULL);

    if (minw <= 0) minw = 1;
    if (minh <= 0) minh = 1;

    if ((pixad = pixaCreate(n)) == NULL)
        return (PIXA *)ERROR_PTR("pixad not made", procName, NULL);


    for (i = 0; i < n; i++) {
        pixaGetPixDimensions(pixam, i, &w, &h, NULL);
        if (w >= minw && h >= minh) {
            if ((pixt1 = pixaGetPix(pixam, i, L_CLONE)) == NULL)
                return (PIXA *)ERROR_PTR("pixt1 not found", procName, NULL);
            box = pixaGetBox(pixam, i, L_COPY);
            pixt2 = pixClipRectangle(pixs, box, NULL);
            pixAnd(pixt2, pixt2, pixt1);
            if ((pixt3 = pixMorphCompSequence(pixt2, sequence, 0)) == NULL)
                return (PIXA *)ERROR_PTR("pixt3 not made", procName, NULL);
            pixaAddPix(pixad, pixt3, L_INSERT);
            pixaAddBox(pixad, box, L_INSERT);
            pixDestroy(&pixt1);
            pixDestroy(&pixt2);
        }
    }

    return pixad;
}
