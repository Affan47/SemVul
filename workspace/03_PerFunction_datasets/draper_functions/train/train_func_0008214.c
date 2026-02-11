fdilate_2_67(l_uint32  *datad,
            l_int32    w,
            l_int32    h,
            l_int32    wpld,
            l_uint32  *datas,
            l_int32    wpls)
{
l_int32             i;
register l_int32    j, pwpls;
register l_uint32  *sptr, *dptr;
l_int32             wpls4;
l_int32             wpls5;
l_int32             wpls13;
l_int32             wpls14;
l_int32             wpls22;
l_int32             wpls23;

    wpls4 = 4 * wpls;
    wpls5 = 5 * wpls;
    wpls13 = 13 * wpls;
    wpls14 = 14 * wpls;
    wpls22 = 22 * wpls;
    wpls23 = 23 * wpls;
    pwpls = (l_uint32)(w + 31) / 32;

    for (i = 0; i < h; i++) {
        sptr = datas + i * wpls;
        dptr = datad + i * wpld;
        for (j = 0; j < pwpls; j++, sptr++, dptr++) {
            *dptr = (*(sptr + wpls23)) |
                    (*(sptr + wpls14)) |
                    (*(sptr + wpls5)) |
                    (*(sptr - wpls4)) |
                    (*(sptr - wpls13)) |
                    (*(sptr - wpls22));
        }
    }
}
