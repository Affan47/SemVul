murmur3_tail(const uint8_t *data, const int nblocks,
			     uint32_t len, const uint32_t c1,
			     const uint32_t c2, uint32_t h1)
{
	const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);

	uint32_t k1 = 0;
	switch (len & 3) {
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];
		k1 *= c1;
		k1 = rotl32(k1, 15);
		k1 *= c2;
		h1 ^= k1;
	};

	return fmix32(h1 ^ len);
}
