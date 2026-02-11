fdilate_1_5(l_uint32  *datad,
            l_int32    w,
            l_int32    h,
            l_int32    wpld,
            l_uint32  *datas,
            l_int32    wpls)
{
l_int32             i;
register l_int32    j, pwpls;
register l_uint32  *sptr, *dptr;

    pwpls = (l_uint32)(w + 31) / 32;

    for (i = 0; i < h; i++) {
        sptr = datas + i * wpls;
        dptr = datad + i * wpld;
        for (j = 0; j < pwpls; j++, sptr++, dptr++) {
            *dptr = ((*(sptr) << 3) | (*(sptr + 1) >> 29)) |
                    ((*(sptr) << 2) | (*(sptr + 1) >> 30)) |
                    ((*(sptr) << 1) | (*(sptr + 1) >> 31)) |
                    (*sptr) |
                    ((*(sptr) >> 1) | (*(sptr - 1) << 31)) |
                    ((*(sptr) >> 2) | (*(sptr - 1) << 30)) |
                    ((*(sptr) >> 3) | (*(sptr - 1) << 29));
        }
    }
}
