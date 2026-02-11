pixLocalExtrema(PIX     *pixs,
                l_int32  maxmin,
                l_int32  minmax,
                PIX    **ppixmin,
                PIX    **ppixmax)
{
PIX  *pixmin, *pixmax, *pixt1, *pixt2;

    PROCNAME("pixLocalExtrema");

    if (!pixs || pixGetDepth(pixs) != 8)
        return ERROR_INT("pixs not defined or not 8 bpp", procName, 1);
    if (!ppixmin && !ppixmax)
        return ERROR_INT("neither &pixmin, &pixmax are defined", procName, 1);
    if (maxmin <= 0) maxmin = 254;
    if (minmax <= 0) minmax = 1;

    if (ppixmin) {
        pixt1 = pixErodeGray(pixs, 3, 3);
        pixmin = pixFindEqualValues(pixs, pixt1);
        pixDestroy(&pixt1);
        pixQualifyLocalMinima(pixs, pixmin, maxmin);
        *ppixmin = pixmin;
    }

    if (ppixmax) {
        pixt1 = pixInvert(NULL, pixs);
        pixt2 = pixErodeGray(pixt1, 3, 3);
        pixmax = pixFindEqualValues(pixt1, pixt2);
        pixDestroy(&pixt2);
        pixQualifyLocalMinima(pixt1, pixmax, 255 - minmax);
        *ppixmax = pixmax;
        pixDestroy(&pixt1);
    }

    return 0;
}
