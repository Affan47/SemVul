pixcmapGetComponentRange(PIXCMAP  *cmap,
                         l_int32   color,
                         l_int32  *pminval,
                         l_int32  *pmaxval)
{
    PROCNAME("pixcmapGetComponentRange");

    if (pminval) *pminval = 0;
    if (pmaxval) *pmaxval = 0;
    if (!pminval && !pmaxval)
        return ERROR_INT("no result requested", procName, 1);

    if (color == L_SELECT_RED) {
        pixcmapGetExtremeValue(cmap, L_SELECT_MIN, pminval, NULL, NULL);
        pixcmapGetExtremeValue(cmap, L_SELECT_MAX, pmaxval, NULL, NULL);
    } else if (color == L_SELECT_GREEN) {
        pixcmapGetExtremeValue(cmap, L_SELECT_MIN, NULL, pminval, NULL);
        pixcmapGetExtremeValue(cmap, L_SELECT_MAX, NULL, pmaxval, NULL);
    } else if (color == L_SELECT_BLUE) {
        pixcmapGetExtremeValue(cmap, L_SELECT_MIN, NULL, NULL, pminval);
        pixcmapGetExtremeValue(cmap, L_SELECT_MAX, NULL, NULL, pmaxval);
    } else {
        return ERROR_INT("invalid color", procName, 1);
    }

    return 0;
}
