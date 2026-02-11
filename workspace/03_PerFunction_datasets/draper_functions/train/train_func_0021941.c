pixMakeHistoHV(PIX     *pixs,
               l_int32  factor,
               NUMA   **pnahue,
               NUMA   **pnaval)
{
l_int32    i, j, w, h, wplt, hval, vval, nd;
l_uint32   pixel;
l_uint32  *datat, *linet;
void     **lined32;
NUMA      *nahue, *naval;
PIX       *pixt, *pixd;

    PROCNAME("pixMakeHistoHV");

    if (pnahue) *pnahue = NULL;
    if (pnaval) *pnaval = NULL;
    if (!pixs || pixGetDepth(pixs) != 32)
        return (PIX *)ERROR_PTR("pixs undefined or not 32 bpp", procName, NULL);

    if (pnahue) {
        nahue = numaCreate(240);
        numaSetCount(nahue, 240);
        *pnahue = nahue;
    }
    if (pnaval) {
        naval = numaCreate(256);
        numaSetCount(naval, 256);
        *pnaval = naval;
    }

    if (factor <= 1)
        pixt = pixClone(pixs);
    else
        pixt = pixScaleBySampling(pixs, 1.0 / (l_float32)factor,
                                  1.0 / (l_float32)factor);


    pixd = pixCreate(256, 240, 32);
    lined32 = pixGetLinePtrs(pixd, NULL);
    pixGetDimensions(pixt, &w, &h, NULL);
    datat = pixGetData(pixt);
    wplt = pixGetWpl(pixt);
    for (i = 0; i < h; i++) {
        linet = datat + i * wplt;
        for (j = 0; j < w; j++) {
            pixel = linet[j];
            hval = (pixel >> L_RED_SHIFT) & 0xff;
            vval = (pixel >> L_BLUE_SHIFT) & 0xff;
            if (pnahue)
                numaShiftValue(nahue, hval, 1.0);
            if (pnaval)
                numaShiftValue(naval, vval, 1.0);
            nd = GET_DATA_FOUR_BYTES(lined32[hval], vval);
            SET_DATA_FOUR_BYTES(lined32[hval], vval, nd + 1);
        }
    }

    FREE(lined32);
    pixDestroy(&pixt);
    return pixd;
}
