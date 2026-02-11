put_float(PutBitContext * pb, float f) {
    int exp, mant;
    uint32_t res = 0;
    mant = (int)ldexp(frexp(f, &exp), 20);
    exp += 788 - 20;
    if (mant < 0) { res |= (1 << 31); mant = -mant; }
    res |= mant | (exp << 21);
    put_bits(pb, 32, res);
}
