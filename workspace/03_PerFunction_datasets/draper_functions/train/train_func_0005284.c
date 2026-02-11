fhmt_1_5(l_uint32  *datad,
         l_int32    w,
         l_int32    h,
         l_int32    wpld,
         l_uint32  *datas,
         l_int32    wpls)
{
l_int32             i;
register l_int32    j, pwpls;
register l_uint32  *sptr, *dptr;
l_int32             wpls2, wpls3, wpls4;
l_int32             wpls5, wpls6;

    wpls2 = 2 * wpls;
    wpls3 = 3 * wpls;
    wpls4 = 4 * wpls;
    wpls5 = 5 * wpls;
    wpls6 = 6 * wpls;
    pwpls = (l_uint32)(w + 31) / 32;

    for (i = 0; i < h; i++) {
        sptr = datas + i * wpls;
        dptr = datad + i * wpld;
        for (j = 0; j < pwpls; j++, sptr++, dptr++) {
            *dptr = ((~*(sptr - wpls6) << 1) | (~*(sptr - wpls6 + 1) >> 31)) &
                    ((*(sptr - wpls6) << 3) | (*(sptr - wpls6 + 1) >> 29)) &
                    (~*(sptr - wpls2)) &
                    ((*(sptr - wpls2) << 2) | (*(sptr - wpls2 + 1) >> 30)) &
                    ((~*(sptr + wpls2) >> 1) | (~*(sptr + wpls2 - 1) << 31)) &
                    ((*(sptr + wpls2) << 1) | (*(sptr + wpls2 + 1) >> 31)) &
                    ((~*(sptr + wpls6) >> 2) | (~*(sptr + wpls6 - 1) << 30)) &
                    (*(sptr + wpls6));
        }
    }
}
