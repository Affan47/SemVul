pixConvertToFPix(PIX     *pixs,
                 l_int32  ncomps)
{
l_int32     w, h, d, i, j, val, wplt, wpld;
l_uint32    uval;
l_uint32   *datat, *linet;
l_float32  *datad, *lined;
PIX        *pixt;
FPIX       *fpixd;

    PROCNAME("pixConvertToFPix");

    if (!pixs)
        return (FPIX *)ERROR_PTR("pixs not defined", procName, NULL);

    if (pixGetColormap(pixs))
        pixt = pixRemoveColormap(pixs, REMOVE_CMAP_TO_GRAYSCALE);
    else if (pixGetDepth(pixs) == 32 && ncomps == 3)
        pixt = pixConvertRGBToLuminance(pixs);
    else
        pixt = pixClone(pixs);

    pixGetDimensions(pixt, &w, &h, &d);
    if ((fpixd = fpixCreate(w, h)) == NULL)
        return (FPIX *)ERROR_PTR("fpixd not made", procName, NULL);
    datat = pixGetData(pixt);
    wplt = pixGetWpl(pixt);
    datad = fpixGetData(fpixd);
    wpld = fpixGetWpl(fpixd);
    for (i = 0; i < h; i++) {
        linet = datat + i * wplt;
        lined = datad + i * wpld;
        if (d == 1) {
            for (j = 0; j < w; j++) {
                val = GET_DATA_BIT(linet, j);
                lined[j] = (l_float32)val;
            }
        }
        else if (d == 2) {
            for (j = 0; j < w; j++) {
                val = GET_DATA_DIBIT(linet, j);
                lined[j] = (l_float32)val;
            }
        }
        else if (d == 4) {
            for (j = 0; j < w; j++) {
                val = GET_DATA_QBIT(linet, j);
                lined[j] = (l_float32)val;
            }
        }
        else if (d == 8) {
            for (j = 0; j < w; j++) {
                val = GET_DATA_BYTE(linet, j);
                lined[j] = (l_float32)val;
            }
        }
        else if (d == 16) {
            for (j = 0; j < w; j++) {
                val = GET_DATA_TWO_BYTES(linet, j);
                lined[j] = (l_float32)val;
            }
        }
        else if (d == 32) {
            for (j = 0; j < w; j++) {
                uval = GET_DATA_FOUR_BYTES(linet, j);
                lined[j] = (l_float32)uval;
            }
        }
    }

    pixDestroy(&pixt);
    return fpixd;
}
