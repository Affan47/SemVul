elfcrc(const uint32_t start, const unsigned char *name, const uint32_t n) {
	uint32_t i, h, g=0;

	h = start;
	for (i=0;i<n;i++) {
		h = (h << 4) + (*name++);
		g = h & 0xf0000000;
		if (g) h ^= (g >> ((sizeof(g)*8)-8));
		h &= ~g;
	}

	return(h);
}
