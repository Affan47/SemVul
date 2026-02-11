pixcmapGenerateFromHisto(PIX      *pixs,
                         l_int32   depth,
                         l_int32  *histo,
                         l_int32   histosize,
                         l_int32   sigbits)
{
l_int32   i, index, shift, rval, gval, bval;
l_uint32  mask;
PIXCMAP  *cmap;

    PROCNAME("pixcmapGenerateFromHisto");

    if (!pixs)
        return (PIXCMAP *)ERROR_PTR("pixs not defined", procName, NULL);
    if (pixGetDepth(pixs) != 32)
        return (PIXCMAP *)ERROR_PTR("pixs not 32 bpp", procName, NULL);
    if (!histo)
        return (PIXCMAP *)ERROR_PTR("histo not defined", procName, NULL);


    cmap = pixcmapCreate(depth);
    shift = 8 - sigbits;
    mask = 0xff >> shift;
    for (i = 0, index = 0; i < histosize; i++) {
        if (histo[i]) {
            rval = (i >> (2 * sigbits)) << shift;
	    gval = ((i >> sigbits) & mask) << shift;
	    bval = (i & mask) << shift;
            pixcmapAddColor(cmap, rval, gval, bval);
            histo[i] = index++;
        }
    }

    return cmap;
}
