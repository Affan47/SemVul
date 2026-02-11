AddMod(unsigned long *a, unsigned long *b, unsigned long *c,
		   size_t n)
{
    for (size_t i = 0; i < n; i++)
	a[i] = b[i] ^ c[i];
}
