pixcmapShiftByComponent(PIXCMAP  *cmap,
                        l_uint32  srcval,
                        l_uint32  dstval)
{
l_int32   i, ncolors, rval, gval, bval;
l_uint32  newval;

    PROCNAME("pixcmapShiftByComponent");

    if (!cmap)
        return ERROR_INT("cmap not defined", procName, 1);

    ncolors = pixcmapGetCount(cmap);
    for (i = 0; i < ncolors; i++) {
        pixcmapGetColor(cmap, i, &rval, &gval, &bval);
        pixelShiftByComponent(rval, gval, bval, srcval, dstval, &newval);
        extractRGBValues(newval, &rval, &gval, &bval);
        pixcmapResetColor(cmap, i, rval, gval, bval);
    }

    return 0;
}
