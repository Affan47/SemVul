dewarpGetTextlineCenters(PIX     *pixs,
                         l_int32  debugflag)
{
char      buf[64];
l_int32   i, w, h, bx, by, nsegs, csize1, csize2;
BOXA     *boxa;
PIX      *pix1, *pix2;
PIXA     *pixa1, *pixa2;
PTA      *pta;
PTAA     *ptaa;

    PROCNAME("dewarpGetTextlineCenters");

    if (!pixs || pixGetDepth(pixs) != 1)
        return (PTAA *)ERROR_PTR("pixs undefined or not 1 bpp", procName, NULL);
    pixGetDimensions(pixs, &w, &h, NULL);


    csize1 = L_MAX(15, w / 80);
    csize2 = L_MAX(30, w / 30);
    snprintf(buf, sizeof(buf), "o1.3 + c%d.1 + o%d.1 + c%d.1",
             csize1, csize1, csize2);
    pix1 = pixMorphSequence(pixs, buf, 0);
    pixDisplayWithTitle(pix1, 0, 800, "pix1", debugflag);


    boxa = pixConnComp(pix1, &pixa1, 8);
    pixDestroy(&pix1);
    boxaDestroy(&boxa);
    if (pixaGetCount(pixa1) == 0) {
        pixaDestroy(&pixa1);
        return NULL;
    }


    pixa2 = pixaSelectBySize(pixa1, 100, 4, L_SELECT_IF_BOTH,
                                   L_SELECT_IF_GT, 0);
    if ((nsegs = pixaGetCount(pixa2)) == 0) {
        pixaDestroy(&pixa1);
        pixaDestroy(&pixa2);
        return NULL;
    }
    if (debugflag) {
        pix2 = pixaDisplay(pixa2, w, h);
        pixDisplayWithTitle(pix2, 800, 800, "pix2", 1);
        pixDestroy(&pix2);
    }


    ptaa = ptaaCreate(nsegs);
    for (i = 0; i < nsegs; i++) {
        pixaGetBoxGeometry(pixa2, i, &bx, &by, NULL, NULL);
        pix2 = pixaGetPix(pixa2, i, L_CLONE);
        pta = dewarpGetMeanVerticals(pix2, bx, by);
        ptaaAddPta(ptaa, pta, L_INSERT);
        pixDestroy(&pix2);
    }
    if (debugflag) {
        pix1 = pixCreateTemplate(pixs);
        pix2 = pixDisplayPtaa(pix1, ptaa);
        pixDisplayWithTitle(pix2, 0, 1400, "pix3", 1);
        pixDestroy(&pix1);
        pixDestroy(&pix2);
    }

    pixaDestroy(&pixa1);
    pixaDestroy(&pixa2);
    return ptaa;
}
