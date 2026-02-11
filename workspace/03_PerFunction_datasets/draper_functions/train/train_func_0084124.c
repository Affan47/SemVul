trie_utf8_getc (const guchar **in,
                gsize inlen)
{
	register const guchar *inptr = *in;
	const guchar *inend = inptr + inlen;
	register guchar c, r;
	register gunichar u, m;

	if (inlen == 0)
		return 0;

	r = *inptr++;
	if (r < 0x80) {
		*in = inptr;
		u = r;
	} else if (r < 0xfe) {
		u = r;
		m = 0x7f80;
		do {
			if (inptr >= inend)
				return 0;

			c = *inptr++;
			if ((c & 0xc0) != 0x80)
				goto error;

			u = (u << 6) | (c & 0x3f);
			r <<= 1;
			m <<= 5;
		} while (r & 0x40);

		*in = inptr;

		u &= ~m;
	} else {
	error:
		*in = (*in)+1;
		u = 0xfffe;
	}

	return u;
}
