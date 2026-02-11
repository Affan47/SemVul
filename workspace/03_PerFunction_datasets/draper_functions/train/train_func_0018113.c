LocateBarcodes(PIX     *pixs,
               PIX    **ppixd,
               l_int32  flag)
{
BOXA    *boxa1, *boxa2, *boxad;
PIX     *pix1, *pix2, *pix3;

    pix1 = pixScale(pixs, 0.5, 0.5);
    pix2 = pixMorphSequence(pix1, "o1.5 + c15.1 + o10.15 + c20.20", flag);
    boxa1 = pixConnComp(pix2, NULL, 8);
    boxa2 = boxaSelectBySize(boxa1, 300, 0, L_SELECT_WIDTH,
                                   L_SELECT_IF_GT, NULL);
    boxad = boxaTransform(boxa2, 0, 0, 2.0, 2.0);
    if (ppixd) {
        pix3 = pixSelectBySize(pix2, 300, 0, 8, L_SELECT_WIDTH,
                                 L_SELECT_IF_GT, NULL);
        *ppixd = pixScale(pix3, 2.0, 2.0);
        pixDestroy(&pix3);
    }

    pixDestroy(&pix1);
    pixDestroy(&pix2);
    boxaDestroy(&boxa1);
    boxaDestroy(&boxa2);
    return boxad;
}
