pow_mod(uintmax_t base, uintmax_t exp, uintmax_t mod)
{
    uintmax_t ret = 1;
    uintmax_t b;

    b = base;

    while (exp)
    {
        if (exp & 1)
            ret = mult_mod(ret, b, mod);
        exp >>= 1;
        b = mult_mod(b, b, mod);
    }
    return (uintmax_t)ret;
}
