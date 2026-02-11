pixCloseBrickDwa(PIX     *pixd,
                 PIX     *pixs,
                 l_int32  hsize,
                 l_int32  vsize)
{
l_int32  bordercolor, bordersize, found;
char    *selnameh, *selnamev;
SELA    *sela;
PIX     *pixt1, *pixt2, *pixt3;

    PROCNAME("pixCloseBrickDwa");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);
    if (pixGetDepth(pixs) != 1)
        return (PIX *)ERROR_PTR("pixs not 1 bpp", procName, pixd);
    if (hsize < 1 || vsize < 1)
        return (PIX *)ERROR_PTR("hsize and vsize not >= 1", procName, pixd);

    if (hsize == 1 && vsize == 1)
        return pixCopy(pixd, pixs);

    sela = selaAddBasic(NULL);
    found = TRUE;
    if (hsize > 1) {
        selnameh = selaGetBrickName(sela, hsize, 1);
        if (!selnameh) found = FALSE;
    }
    if (vsize > 1) {
        selnamev = selaGetBrickName(sela, 1, vsize);
        if (!selnamev) found = FALSE;
    }
    selaDestroy(&sela);
    if (!found) {
        L_INFO("Calling the decomposable dwa function", procName);
	if (selnameh) FREE(selnameh);
	if (selnamev) FREE(selnamev);
	return pixCloseCompBrickDwa(pixd, pixs, hsize, vsize);
    }


    bordercolor = getMorphBorderPixelColor(L_MORPH_ERODE, 1);
    if (bordercolor == 0)
        bordersize = 64;
    else
        bordersize = 32;
    pixt1 = pixAddBorder(pixs, bordersize, 0);

    if (vsize == 1) {
        pixt2 = pixFMorphopGen_1(NULL, pixt1, L_MORPH_CLOSE, selnameh);
        FREE(selnameh);
    }
    else if (hsize == 1) {
        pixt2 = pixFMorphopGen_1(NULL, pixt1, L_MORPH_CLOSE, selnamev);
        FREE(selnamev);
    }
    else {
        pixt3 = pixFMorphopGen_1(NULL, pixt1, L_MORPH_DILATE, selnameh);
        pixt2 = pixFMorphopGen_1(NULL, pixt3, L_MORPH_DILATE, selnamev);
        pixFMorphopGen_1(pixt3, pixt2, L_MORPH_ERODE, selnameh);
        pixFMorphopGen_1(pixt2, pixt3, L_MORPH_ERODE, selnamev);
        FREE(selnameh);
        FREE(selnamev);
        pixDestroy(&pixt3);
    }
    pixt3 = pixRemoveBorder(pixt2, bordersize);
    pixDestroy(&pixt1);
    pixDestroy(&pixt2);

    if (!pixd)
        return pixt3;
    pixCopy(pixd, pixt3);
    pixDestroy(&pixt3);
    return pixd;
}
