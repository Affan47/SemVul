pixcmapHasColor(PIXCMAP  *cmap,
                l_int32  *pcolor)
{
l_int32   n, i;
l_int32  *rmap, *gmap, *bmap;

    PROCNAME("pixcmapHasColor");

    if (!cmap)
        return ERROR_INT("cmap not defined", procName, 1);
    if (!pcolor)
        return ERROR_INT("&color not defined", procName, 1);
    *pcolor = FALSE;

    if (pixcmapToArrays(cmap, &rmap, &gmap, &bmap))
        return ERROR_INT("colormap arrays not made", procName, 1);
    n = pixcmapGetCount(cmap);
    for (i = 0; i < n; i++) {
        if ((rmap[i] != gmap[i]) || (rmap[i] != bmap[i])) {
            *pcolor = TRUE;
            break;
        }
    }

    FREE(rmap);
    FREE(gmap);
    FREE(bmap);
    return 0;
}
