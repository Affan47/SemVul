AddLsh6(unsigned long * c, const unsigned long * a, const unsigned long * b, long n)
{
    unsigned long cy = 0UL, t;

    long i;

    for (i = 0; i < n; i++) {
	t = a[i] ^ ((b[i] << 6) | cy);
	cy = b[i] >> (GF2X_WORDSIZE - 6);
	c[i] = t;
    }
    return cy;
}
