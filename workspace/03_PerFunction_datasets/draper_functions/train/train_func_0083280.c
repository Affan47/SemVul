pixcmapGenerateFromMedianCuts(L_HEAP   *lh,
                              l_int32  *histo,
                              l_int32   sigbits)
{
l_int32   index, rval, gval, bval;
L_BOX3D  *vbox;
PIXCMAP  *cmap;

    PROCNAME("pixcmapGenerateFromMedianCuts");

    if (!lh)
        return (PIXCMAP *)ERROR_PTR("lh not defined", procName, NULL);
    if (!histo)
        return (PIXCMAP *)ERROR_PTR("histo not defined", procName, NULL);

    rval = gval = bval = 0;
    cmap = pixcmapCreate(8);
    index = 0;
    while (lheapGetCount(lh) > 0) {
        vbox = (L_BOX3D *)lheapRemove(lh);
        vboxGetAverageColor(vbox, histo, sigbits, index, &rval, &gval, &bval);
        pixcmapAddColor(cmap, rval, gval, bval);
        FREE(vbox);
        index++;
    }

    return cmap;
}
