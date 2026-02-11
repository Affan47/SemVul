nr_R8G8B8A8_N_EMPTY_R8G8B8A8_N (unsigned char *px, int w, int h, int rs, const unsigned char *spx, int srs, unsigned int alpha)
{
	unsigned int r, c;

	for (r = h; r > 0; r--) {
		if (alpha == 0) {
			memset(px, 0x0, 4 * w);
		} else if (alpha == 255) {
			memcpy(px, spx, 4 * w);
		} else {
			unsigned char *d = px;
			const unsigned char *s = spx;
			for (c = w; c > 0; c--) {
				*d++ = *s++;
				*d++ = *s++;
				*d++ = *s++;
				*d++ = NR_PREMUL_111(*s, alpha);
				s++;
			}
		}
		px += rs;
		spx += srs;
	}
}
