av_dbl2ext(double d){
    struct AVExtFloat ext= {{0}};
    int e, i; double f; uint64_t m;

    f = fabs(frexp(d, &e));
    if (f >= 0.5 && f < 1) {
        e += 16382;
        ext.exponent[0] = e>>8;
        ext.exponent[1] = e;
        m = (uint64_t)ldexp(f, 64);
        for (i=0; i < 8; i++)
            ext.mantissa[i] = m>>(56-(i<<3));
    } else if (f != 0.0) {
        ext.exponent[0] = 0x7f; ext.exponent[1] = 0xff;
        if (f != 1/0.0)
            ext.mantissa[0] = ~0;
    }
    if (d < 0)
        ext.exponent[0] |= 0x80;
    return ext;
}
