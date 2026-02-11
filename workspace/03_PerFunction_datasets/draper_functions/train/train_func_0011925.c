sph_panama(void *cc, const void *data, size_t len)
{
	sph_panama_context *sc;
	unsigned current;
	size_t rlen;

	if (len < (2 * sizeof sc->data)) {
		panama_short(cc, data, len);
		return;
	}
	sc = cc;
	current = sc->data_ptr;
	if (current > 0) {
		unsigned t;

		t = (sizeof sc->data) - current;
		panama_short(sc, data, t);
		data = (const unsigned char *)data + t;
		len -= t;
	}
#if !SPH_UNALIGNED
	if (((SPH_UPTR)data & 3) != 0) {
		panama_short(sc, data, len);
		return;
	}
#endif
	panama_push(sc, data, len >> 5);
	rlen = len & 31;
	if (rlen > 0)
		memcpy(sc->data,
			(const unsigned char *)data + len - rlen, rlen);
	sc->data_ptr = rlen;
}
