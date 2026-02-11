skein_big_close(sph_skein_big_context *sc, unsigned ub, unsigned n,
	void *dst, size_t out_len)
{
	unsigned char *buf;
	size_t ptr;
	unsigned et;
	int i;
#if SPH_SMALL_FOOTPRINT_SKEIN
	size_t u;
#endif
	DECL_STATE_BIG


	if (n != 0) {
		unsigned z;
		unsigned char x;

		z = 0x80 >> n;
		x = ((ub & -z) | z) & 0xFF;
		skein_big_core(sc, &x, 1);
	}

	buf = sc->buf;
	ptr = sc->ptr;


	READ_STATE_BIG(sc);
	memset(buf + ptr, 0, (sizeof sc->buf) - ptr);
	et = 352 + ((bcount == 0) << 7) + (n != 0);
	for (i = 0; i < 2; i ++) {
		UBI_BIG(et, ptr);
		if (i == 0) {
			memset(buf, 0, sizeof sc->buf);
			bcount = 0;
			et = 510;
			ptr = 8;
		}
	}

#if SPH_SMALL_FOOTPRINT_SKEIN


	for (u = 0; u < out_len; u += 8)
		sph_enc64le_aligned(buf + u, h[u >> 3]);
	memcpy(dst, buf, out_len);

#else

	sph_enc64le_aligned(buf +  0, h0);
	sph_enc64le_aligned(buf +  8, h1);
	sph_enc64le_aligned(buf + 16, h2);
	sph_enc64le_aligned(buf + 24, h3);
	sph_enc64le_aligned(buf + 32, h4);
	sph_enc64le_aligned(buf + 40, h5);
	sph_enc64le_aligned(buf + 48, h6);
	sph_enc64le_aligned(buf + 56, h7);
	memcpy(dst, buf, out_len);

#endif
}
