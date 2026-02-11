pixUsesCmapColor(PIX      *pixs,
                 l_int32  *pcolor)
{
l_int32   n, i, rval, gval, bval, numpix;
NUMA     *na;
PIXCMAP  *cmap;

    PROCNAME("pixUsesCmapColor");

    if (!pcolor)
        return ERROR_INT("&color not defined", procName, 1);
    *pcolor = 0;
    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);

    if ((cmap = pixGetColormap(pixs)) == NULL)
        return 0;

    pixcmapHasColor(cmap, pcolor);
    if (*pcolor == 0)
        return 0;


    na = pixGetGrayHistogram(pixs, 1);
    n = pixcmapGetCount(cmap);
    for (i = 0; i < n; i++) {
        pixcmapGetColor(cmap, i, &rval, &gval, &bval);
        numaGetIValue(na, i, &numpix);
        if ((rval != gval || rval != bval) && numpix) {
            *pcolor = 1;
            break;
        }
    }
    numaDestroy(&na);

    return 0;
}
