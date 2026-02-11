scaleToGray2Low(l_uint32  *datad,
                l_int32    wd,
                l_int32    hd,
                l_int32    wpld,
                l_uint32  *datas,
                l_int32    wpls,
                l_uint32  *sumtab,
                l_uint8   *valtab)
{
l_int32    i, j, l, k, m, wd4, extra;
l_uint32   sbyte1, sbyte2, sum;
l_uint32  *lines, *lined;


    wd4 = wd & 0xfffffffc;
    extra = wd - wd4;
    for (i = 0, l = 0; i < hd; i++, l += 2) {
        lines = datas + l * wpls;
        lined = datad + i * wpld;
        for (j = 0, k = 0; j < wd4; j += 4, k++) {
            sbyte1 = GET_DATA_BYTE(lines, k);
            sbyte2 = GET_DATA_BYTE(lines + wpls, k);
            sum = sumtab[sbyte1] + sumtab[sbyte2];
            SET_DATA_BYTE(lined, j, valtab[sum >> 24]);
            SET_DATA_BYTE(lined, j + 1, valtab[(sum >> 16) & 0xff]);
            SET_DATA_BYTE(lined, j + 2, valtab[(sum >> 8) & 0xff]);
            SET_DATA_BYTE(lined, j + 3, valtab[sum & 0xff]);
        }
        if (extra > 0) {
            sbyte1 = GET_DATA_BYTE(lines, k);
            sbyte2 = GET_DATA_BYTE(lines + wpls, k);
            sum = sumtab[sbyte1] + sumtab[sbyte2];
            for (m = 0; m < extra; m++) {
                SET_DATA_BYTE(lined, j + m,
                              valtab[((sum >> (24 - 8 * m)) & 0xff)]);
            }
        }

    }

    return;
}
