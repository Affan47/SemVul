bignum_mod_short(Bignum number, unsigned short modulus)
{
    BignumDblInt mod, r;
    int i;

    r = 0;
    mod = modulus;
    for (i = number[0]; i > 0; i--)
	r = (r * (BIGNUM_TOP_BIT % mod) * 2 + number[i] % mod) % mod;
    return (unsigned short) r;
}
