type2_put_fixed(stream *s, fixed v)
{
    if (fixed_is_int(v))
        type2_put_int(s, fixed2int_var(v));
    else if (v >= int2fixed(-32768) && v < int2fixed(32768)) {

        spputc(s, cx_num4);
        sputc4(s, v << (16 - _fixed_shift));
    } else {
        type2_put_int(s, fixed2int_var(v));
        type2_put_fixed(s, fixed_fraction(v));
        type2_put_op(s, CE_OFFSET + ce2_add);
    }
}
