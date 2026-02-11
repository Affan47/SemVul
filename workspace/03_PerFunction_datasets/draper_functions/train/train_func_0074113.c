Double_To_Bignum (double d) {
    Object big;
    int expo, size;
    double mantissa = frexp (d, &expo);
    register gran_t *p;

    if (expo <= 0 || mantissa == 0.0)
        return Make_Uninitialized_Bignum (0);
    size = (expo + (16-1)) / 16;
    big = Make_Uninitialized_Bignum (size);
    BIGNUM(big)->usize = size;
    if (mantissa < 0.0) {
        BIGNUM(big)->minusp = True;
        mantissa = -mantissa;
    }
    p = BIGNUM(big)->data;
    memset (p, 0, size * sizeof (gran_t));
    p += size;
    if (expo &= (16-1))
        mantissa = ldexp (mantissa, expo - 16);
    while (mantissa != 0.0) {
        if (--size < 0)
            break;
        mantissa *= 65536.0;
        *--p = (int)mantissa;
        mantissa -= *p;
    }
    Bignum_Normalize_In_Place (BIGNUM(big));
    return Reduce_Bignum (big);
}
