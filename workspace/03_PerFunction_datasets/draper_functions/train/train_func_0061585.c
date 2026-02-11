pixRenderRandomCmapPtaa(PIX     *pix,
                        PTAA    *ptaa,
                        l_int32  polyflag,
                        l_int32  width,
                        l_int32  closeflag)
{
l_int32   i, n, index, rval, gval, bval;
PIXCMAP  *cmap;
PTA      *pta, *ptat;
PIX      *pixd;

    PROCNAME("pixRenderRandomCmapPtaa");

    if (!pix)
        return (PIX *)ERROR_PTR("pix not defined", procName, NULL);
    if (!ptaa)
        return (PIX *)ERROR_PTR("ptaa not defined", procName, NULL);
    if (width < 1) {
        L_WARNING("width < 1; setting to 1\n", procName);
        width = 1;
    }

    pixd = pixConvertTo8(pix, FALSE);
    cmap = pixcmapCreateRandom(8, 1, 1);
    pixSetColormap(pixd, cmap);

    if ((n = ptaaGetCount(ptaa)) == 0)
        return pixd;

    for (i = 0; i < n; i++) {
        index = 1 + (i % 254);
        pixcmapGetColor(cmap, index, &rval, &gval, &bval);
        pta = ptaaGetPta(ptaa, i, L_CLONE);
        if (polyflag)
            ptat = generatePtaPolyline(pta, width, closeflag, 0);
        else
            ptat = ptaClone(pta);
        pixRenderPtaArb(pixd, ptat, rval, gval, bval);
        ptaDestroy(&pta);
        ptaDestroy(&ptat);
    }

    return pixd;
}
