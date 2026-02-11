ferode_2_44(l_uint32  *datad,
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
            *dptr = ((*(sptr) >> 14) | (*(sptr - 1) << 18)) &
                    ((*(sptr) >> 7) | (*(sptr - 1) << 25)) &
                    (*sptr) &
                    ((*(sptr) << 7) | (*(sptr + 1) >> 25)) &
                    ((*(sptr) << 14) | (*(sptr + 1) >> 18));
        }
    }
}
