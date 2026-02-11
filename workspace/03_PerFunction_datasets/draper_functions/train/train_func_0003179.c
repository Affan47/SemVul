fpixaDisplayQuadtree(FPIXA    *fpixa,
                     l_int32   factor)
{
char       buf[256];
l_int32    nlevels, i, mag, w;
L_BMF     *bmf;
FPIX      *fpix;
PIX       *pixt1, *pixt2, *pixt3, *pixt4, *pixd;
PIXA      *pixat;

    PROCNAME("fpixaDisplayQuadtree");

    if (!fpixa)
        return (PIX *)ERROR_PTR("fpixa not defined", procName, NULL);

    if ((nlevels = fpixaGetCount(fpixa)) == 0)
        return (PIX *)ERROR_PTR("pixas empty", procName, NULL);

    bmf = bmfCreate("./fonts", 6);
    pixat = pixaCreate(nlevels);
    for (i = 0; i < nlevels; i++) {
        fpix = fpixaGetFPix(fpixa, i, L_CLONE);
        pixt1 = fpixConvertToPix(fpix, 8, L_CLIP_TO_ZERO, 0);
        mag = factor * (1 << (nlevels - i - 1));
        pixt2 = pixExpandReplicate(pixt1, mag);
        pixt3 = pixConvertTo32(pixt2);
        snprintf(buf, sizeof(buf), "Level %d\n", i);
        pixt4 = pixAddSingleTextblock(pixt3, bmf, buf, 0xff000000,
                                      L_ADD_BELOW, NULL);
        pixaAddPix(pixat, pixt4, L_INSERT);
        fpixDestroy(&fpix);
        pixDestroy(&pixt1);
        pixDestroy(&pixt2);
        pixDestroy(&pixt3);
    }
    w = pixGetWidth(pixt4);
    pixd = pixaDisplayTiledInRows(pixat, 32, nlevels * (w + 80), 1.0, 0, 30, 2);

    pixaDestroy(&pixat);
    bmfDestroy(&bmf);
    return pixd;
}
