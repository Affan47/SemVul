fnv_hash(const unsigned char *s, unsigned int bits, unsigned int unused)
{
	uint32_t h = FNV1_32_INIT;
	bits = 32 - bits;
	while(*s)
	{
		h ^= *s++;
		h += (h << 1) + (h << 4) + (h << 7) + (h << 8) + (h << 24);
	}
	h = (h >> bits) ^ (h & ((2 ^ bits) - 1));
	return h;
}
