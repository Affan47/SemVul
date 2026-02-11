pixRenderBoxaArb(PIX     *pix,
                 BOXA    *boxa,
                 l_int32  width,
                 l_uint8  rval,
                 l_uint8  gval,
                 l_uint8  bval)
{
PTA  *pta;

    PROCNAME("pixRenderBoxaArb");

    if (!pix)
        return ERROR_INT("pix not defined", procName, 1);
    if (!boxa)
        return ERROR_INT("boxa not defined", procName, 1);
    if (width < 1) {
        L_WARNING("width < 1; setting to 1\n", procName);
        width = 1;
    }

    if ((pta = generatePtaBoxa(boxa, width, 0)) == NULL)
        return ERROR_INT("pta not made", procName, 1);
    pixRenderPtaArb(pix, pta, rval, gval, bval);
    ptaDestroy(&pta);
    return 0;
}
