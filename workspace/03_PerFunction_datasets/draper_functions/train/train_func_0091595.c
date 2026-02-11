absDifferenceLow(l_uint32  *datad,
                 l_int32    w,
                 l_int32    h,
                 l_int32    wpld,
                 l_uint32  *datas1,
                 l_uint32  *datas2,
                 l_int32    d,
                 l_int32    wpls)
{
l_int32    i, j, val1, val2, diff;
l_uint32   word1, word2;
l_uint32  *lines1, *lines2, *lined, *pdword;

    PROCNAME("absDifferenceLow");

    switch (d)
    {
    case 8:
        for (i = 0; i < h; i++) {
            lines1 = datas1 + i * wpls;
            lines2 = datas2 + i * wpls;
            lined = datad + i * wpld;
            for (j = 0; j < w; j++) {
                val1 = GET_DATA_BYTE(lines1, j);
                val2 = GET_DATA_BYTE(lines2, j);
                diff = L_ABS(val1 - val2);
                SET_DATA_BYTE(lined, j, diff);
            }
        }
        break;
    case 16:
        for (i = 0; i < h; i++) {
            lines1 = datas1 + i * wpls;
            lines2 = datas2 + i * wpls;
            lined = datad + i * wpld;
            for (j = 0; j < w; j++) {
                val1 = GET_DATA_TWO_BYTES(lines1, j);
                val2 = GET_DATA_TWO_BYTES(lines2, j);
                diff = L_ABS(val1 - val2);
                SET_DATA_TWO_BYTES(lined, j, diff);
            }
        }
        break;
    case 32:
        for (i = 0; i < h; i++) {
            lines1 = datas1 + i * wpls;
            lines2 = datas2 + i * wpls;
            lined = datad + i * wpld;
            for (j = 0; j < w; j++) {
                word1 = lines1[j];
                word2 = lines2[j];
                pdword = lined + j;
                val1 = GET_DATA_BYTE(&word1, COLOR_RED);
                val2 = GET_DATA_BYTE(&word2, COLOR_RED);
                diff = L_ABS(val1 - val2);
                SET_DATA_BYTE(pdword, COLOR_RED, diff);
                val1 = GET_DATA_BYTE(&word1, COLOR_GREEN);
                val2 = GET_DATA_BYTE(&word2, COLOR_GREEN);
                diff = L_ABS(val1 - val2);
                SET_DATA_BYTE(pdword, COLOR_GREEN, diff);
                val1 = GET_DATA_BYTE(&word1, COLOR_BLUE);
                val2 = GET_DATA_BYTE(&word2, COLOR_BLUE);
                diff = L_ABS(val1 - val2);
                SET_DATA_BYTE(pdword, COLOR_BLUE, diff);
            }
        }
        break;
    default:
        L_ERROR("source depth must be 8, 16 or 32 bpp", procName);
        break;
    }

    return;
}
