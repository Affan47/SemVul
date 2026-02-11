pixColorSegmentRemoveColors(PIX     *pixd,
                            PIX     *pixs,
                            l_int32  finalcolors)
{
l_int32    i, npix, minpix, ncolors, index, tempcolor;
l_int32   *tab;
NUMA      *na, *nasi;
PIX       *pixm;
PIXCMAP   *cmap;

    PROCNAME("pixColorSegmentRemoveColors");

    if (!pixd)
        return ERROR_INT("pixd not defined", procName, 1);
    if (pixGetDepth(pixd) != 8)
        return ERROR_INT("pixd not 8 bpp", procName, 1);
    if ((cmap = pixGetColormap(pixd)) == NULL)
        return ERROR_INT("cmap not found", procName, 1);
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    ncolors = pixcmapGetCount(cmap);
    if (finalcolors >= ncolors)
        return 0;


    na = pixGetGrayHistogram(pixd, 1);
    if ((nasi = numaGetSortIndex(na, L_SORT_DECREASING)) == NULL)
        return ERROR_INT("nasi not made", procName, 1);
    numaGetIValue(nasi, finalcolors - 1, &index);
    tempcolor = index;
    numaGetIValue(na, index, &minpix);
    if ((tab = (l_int32 *)CALLOC(256, sizeof(l_int32))) == NULL)
        return ERROR_INT("tab not made", procName, 1);
    for (i = 0; i < ncolors; i++) {
        numaGetIValue(na, i, &npix);
        if (npix < minpix && npix > 0)
            tab[i] = 1;
    }
    pixm = pixMakeMaskFromLUT(pixd, tab);
    FREE(tab);


    pixSetMasked(pixd, pixm, tempcolor);


    pixRemoveUnusedColors(pixd);


    pixAssignToNearestColor(pixd, pixs, pixm, LEVEL_IN_OCTCUBE, NULL);

    pixDestroy(&pixm);
    numaDestroy(&na);
    numaDestroy(&nasi);
    return 0;
}
