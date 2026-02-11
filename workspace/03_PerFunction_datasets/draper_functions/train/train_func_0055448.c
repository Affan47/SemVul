convertToNUpPixa(const char  *dir,
                 const char  *substr,
                 l_int32      nx,
                 l_int32      ny,
                 l_int32      tw,
                 l_int32      spacing,
                 l_int32      border,
                 const char  *fontdir)
{
l_int32    i, j, k, nt, n2, nout, d;
char      *fname, *tail;
L_BMF     *bmf;
PIX       *pix1, *pix2, *pix3, *pix4;
PIXA      *pixat, *pixad;
SARRAY    *sa;

    PROCNAME("convertToNUpPixa");

    if (!dir)
        return (PIXA *)ERROR_PTR("dir not defined", procName, NULL);
    if (nx < 1 || ny < 1 || nx > 50 || ny > 50)
        return (PIXA *)ERROR_PTR("invalid tiling N-factor", procName, NULL);
    if (tw < 20)
        return (PIXA *)ERROR_PTR("tw must be >= 20", procName, NULL);

    sa = getSortedPathnamesInDirectory(dir, substr, 0, 0);
    nt = sarrayGetCount(sa);
    n2 = nx * ny;
    nout = (nt + n2 - 1) / n2;
    pixad = pixaCreate(nout);
    bmf = (fontdir) ? bmfCreate(fontdir, 6) : NULL;
    for (i = 0, j = 0; i < nout; i++) {
        pixat = pixaCreate(n2);
        for (k = 0; k < n2 && j < nt; j++, k++) {
            fname = sarrayGetString(sa, j, L_NOCOPY);
            if ((pix1 = pixRead(fname)) == NULL) {
                L_ERROR("image not read from %s\n", procName, fname);
                continue;
            }
            pix2 = pixScaleToSize(pix1, tw, 0);
            if (fontdir) {
                splitPathAtDirectory(fname, NULL, &tail);
                pix3 = pixAddSingleTextline(pix2, bmf, tail, 0xff000000,
                                            L_ADD_BELOW);
                FREE(tail);
            } else {
                pix3 = pixClone(pix2);
            }
            pixaAddPix(pixat, pix3, L_INSERT);
            pixDestroy(&pix1);
            pixDestroy(&pix2);
        }
        if (pixaGetCount(pixat) == 0) continue;
        pixaGetRenderingDepth(pixat, &d);

        pix4 = pixaDisplayTiledAndScaled(pixat, d, tw + 2 * border, nx, 0,
                                         spacing, border);
        pixaAddPix(pixad, pix4, L_INSERT);
        pixaDestroy(&pixat);
    }

    sarrayDestroy(&sa);
    bmfDestroy(&bmf);
    return pixad;
}
