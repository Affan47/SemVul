lam_copyrev4(void *dest, void *src, int num)
{
#ifdef LAM_USE_SHIFTING
	int		i;
	uint4		old;
	uint4		*s, *d;

	d = dest;
	s = src;

	for (i = 0; i < num; ++i, ++s, ++d) {
		old = *s;
		*d = (old & 0x000000FF) << 16;
		*d = (*d | (old & 0x0000FF00)) << 8;
		old >>= 8;
		*d |= (old & 0x0000FF00);
		old >>= 16;
		*d |= (old & 0x000000FF);
	}
#else
        unsigned char   *d, *s;
        int             i;

        d = dest;
        s = src;
        num *= 4;

        for (i = 0; i < num; i += 4) {
                d[i] = s[i + 3];
                d[i + 1] = s[i + 2];
                d[i + 2] = s[i + 1];
                d[i + 3] = s[i];
        }
#endif
}
