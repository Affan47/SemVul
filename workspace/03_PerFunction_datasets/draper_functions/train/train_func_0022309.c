fdilate_1_28(l_uint32  *datad,
            l_int32    w,
            l_int32    h,
            l_int32    wpld,
            l_uint32  *datas,
            l_int32    wpls)
{
l_int32             i;
register l_int32    j, pwpls;
register l_uint32  *sptr, *dptr;
l_int32             wpls2;

    wpls2 = 2 * wpls;
    pwpls = (l_uint32)(w + 31) / 32;

    for (i = 0; i < h; i++) {
        sptr = datas + i * wpls;
        dptr = datad + i * wpld;
        for (j = 0; j < pwpls; j++, sptr++, dptr++) {
            *dptr = (*(sptr + wpls2)) |
                    (*(sptr + wpls)) |
                    (*sptr) |
                    (*(sptr - wpls)) |
                    (*(sptr - wpls2));
        }
    }
}
