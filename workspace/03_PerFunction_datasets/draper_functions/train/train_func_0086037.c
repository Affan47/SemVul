pixSnapColorCmap(PIX      *pixd,
                 PIX      *pixs,
                 l_uint32  srcval,
                 l_uint32  dstval,
                 l_int32   diff)
{
l_int32    i, ncolors, index, found;
l_int32    rval, gval, bval, rsval, gsval, bsval, rdval, gdval, bdval;
l_int32   *tab;
PIX       *pixm;
PIXCMAP   *cmap;

    PROCNAME("pixSnapColorCmap");

    if (!pixs)
        return (PIX *)ERROR_PTR("pixs not defined", procName, pixd);
    if (!pixGetColormap(pixs))
        return (PIX *)ERROR_PTR("cmap not found", procName, pixd);
    if (pixd && (pixd != pixs))
        return (PIX *)ERROR_PTR("pixd not null or == pixs", procName, pixd);

    if (!pixd)
        pixd = pixCopy(NULL, pixs);


    cmap = pixGetColormap(pixd);
    ncolors = pixcmapGetCount(cmap);
    extractRGBValues(srcval, &rsval, &gsval, &bsval);
    extractRGBValues(dstval, &rdval, &gdval, &bdval);
    found = FALSE;
    if (pixcmapGetFreeCount(cmap) == 0) {
        for (i = 0; i < ncolors; i++) {
            pixcmapGetColor(cmap, i, &rval, &gval, &bval);
            if ((L_ABS(rval - rsval) <= diff) &&
                (L_ABS(gval - gsval) <= diff) &&
                (L_ABS(bval - bsval) <= diff)) {
                index = i;
                pixcmapResetColor(cmap, index, rdval, gdval, bdval);
                found = TRUE;
                break;
            }
        }
    } else {
        pixcmapAddColor(cmap, rdval, gdval, bdval);
        ncolors = pixcmapGetCount(cmap);
        index = ncolors - 1;
        found = TRUE;
    }

    if (!found) {
        L_INFO("nothing to do\n", procName);
        return pixd;
    }


    if ((tab = (l_int32 *)CALLOC(256, sizeof(l_int32))) == NULL)
        return (PIX *)ERROR_PTR("tab not made", procName, pixd);
    for (i = 0; i < ncolors; i++) {
        pixcmapGetColor(cmap, i, &rval, &gval, &bval);
        if ((L_ABS(rval - rsval) <= diff) &&
            (L_ABS(gval - gsval) <= diff) &&
            (L_ABS(bval - bsval) <= diff))
            tab[i] = 1;
    }
    pixm = pixMakeMaskFromLUT(pixd, tab);
    FREE(tab);


    pixSetMasked(pixd, pixm, dstval);
    pixDestroy(&pixm);


    pixRemoveUnusedColors(pixd);

    return pixd;
}
