ff_h263_encode_motion(MpegEncContext * s, int val, int f_code)
{
    int range, l, bit_size, sign, code, bits;

    if (val == 0) {

        code = 0;
        put_bits(&s->pb, mvtab[code][1], mvtab[code][0]);
    } else {
        bit_size = f_code - 1;
        range = 1 << bit_size;

        l= INT_BIT - 6 - bit_size;
        val = (val<<l)>>l;
        sign = val>>31;
        val= (val^sign)-sign;
        sign&=1;

        val--;
        code = (val >> bit_size) + 1;
        bits = val & (range - 1);

        put_bits(&s->pb, mvtab[code][1] + 1, (mvtab[code][0] << 1) | sign);
        if (bit_size > 0) {
            put_bits(&s->pb, bit_size, bits);
        }
    }
}
