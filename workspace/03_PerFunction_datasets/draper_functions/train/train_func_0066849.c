pixColorSegmentRemoveColors(PIX     *pixd,
                            PIX     *pixs,
                            l_int32  finalcolors)
{
l_int32    i, ncolors, index, tempindex;
l_int32   *tab;
l_uint32   tempcolor;
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


    na = pixGetCmapHistogram(pixd, 1);
    if ((nasi = numaGetSortIndex(na, L_SORT_DECREASING)) == NULL) {
        numaDestroy(&na);
        return ERROR_INT("nasi not made", procName, 1);
    }
    numaGetIValue(nasi, finalcolors - 1, &tempindex);
    pixcmapGetColor32(cmap, tempindex, &tempcolor);
    tab = (l_int32 *)CALLOC(256, sizeof(l_int32));
    for (i = finalcolors; i < ncolors; i++) {
        numaGetIValue(nasi, i, &index);
        tab[index] = 1;
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
