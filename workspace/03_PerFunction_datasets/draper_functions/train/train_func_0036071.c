fhmt_1_2(l_uint32  *datad,
         l_int32    w,
         l_int32    h,
         l_int32    wpld,
         l_uint32  *datas,
         l_int32    wpls)
{
l_int32              i;
register l_int32     j, pwpls;
register l_uint32   *sptr, *dptr;
l_int32              wpls2, wpls3;

    wpls2 = 2 * wpls;
    wpls3 = 3 * wpls;
    pwpls = (l_uint32)(w + 31) / 32;

    for (i = 0; i < h; i++) {
        sptr = datas + i * wpls;
        dptr = datad + i * wpld;
        for (j = 0; j < pwpls; j++, sptr++, dptr++) {
            *dptr = ((*(sptr - wpls3) >> 3) | (*(sptr - wpls3 - 1) << 29)) &
                    ((*(sptr - wpls3) >> 2) | (*(sptr - wpls3 - 1) << 30)) &
                    ((*(sptr - wpls3) >> 1) | (*(sptr - wpls3 - 1) << 31)) &
                    (*(sptr - wpls3)) &
                    ((*(sptr - wpls3) << 1) | (*(sptr - wpls3 + 1) >> 31)) &
                    ((*(sptr - wpls3) << 2) | (*(sptr - wpls3 + 1) >> 30)) &
                    ((*(sptr - wpls2) >> 3) | (*(sptr - wpls2 - 1) << 29)) &
                    ((*(sptr - wpls) >> 3) | (*(sptr - wpls - 1) << 29)) &
                    (~*(sptr - wpls)) &
                    ((*(sptr) >> 3) | (*(sptr - 1) << 29)) &
                    ((~*(sptr) >> 1) | (~*(sptr - 1) << 31)) &
                    (~*sptr) &
                    ((~*(sptr) << 1) | (~*(sptr + 1) >> 31)) &
                    ((*(sptr + wpls) >> 3) | (*(sptr + wpls - 1) << 29)) &
                    (~*(sptr + wpls)) &
                    ((~*(sptr + wpls) << 1) | (~*(sptr + wpls + 1) >> 31));
        }
    }
}
