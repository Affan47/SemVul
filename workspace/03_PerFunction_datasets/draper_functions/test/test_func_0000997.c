pixAddConstantGray(PIX      *pixs,
                   l_int32   val)
{
l_int32    i, j, w, h, d, wpl, pval;
l_uint32  *data, *line;

    PROCNAME("pixAddConstantGray");

    if (!pixs)
        return ERROR_INT("pixs not defined", procName, 1);
    pixGetDimensions(pixs, &w, &h, &d);
    if (d != 8 && d != 16 && d != 32)
        return ERROR_INT("pixs not 8, 16 or 32 bpp", procName, 1);

    data = pixGetData(pixs);
    wpl = pixGetWpl(pixs);
    for (i = 0; i < h; i++) {
        line = data + i * wpl;
        if (d == 8) {
            if (val < 0) {
                for (j = 0; j < w; j++) {
                    pval = GET_DATA_BYTE(line, j);
                    pval = L_MAX(0, pval + val);
                    SET_DATA_BYTE(line, j, pval);
                }
            } else {
                for (j = 0; j < w; j++) {
                    pval = GET_DATA_BYTE(line, j);
                    pval = L_MIN(255, pval + val);
                    SET_DATA_BYTE(line, j, pval);
                }
            }
        } else if (d == 16) {
            if (val < 0) {
                for (j = 0; j < w; j++) {
                    pval = GET_DATA_TWO_BYTES(line, j);
                    pval = L_MAX(0, pval + val);
                    SET_DATA_TWO_BYTES(line, j, pval);
                }
            } else {
                for (j = 0; j < w; j++) {
                    pval = GET_DATA_TWO_BYTES(line, j);
                    pval = L_MIN(0xffff, pval + val);
                    SET_DATA_TWO_BYTES(line, j, pval);
                }
            }
        } else {
            for (j = 0; j < w; j++)
                *(line + j) += val;
        }
    }

    return 0;
}
