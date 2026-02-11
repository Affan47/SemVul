base32_decode(const char* src, unsigned char* dst, size_t len) {
	size_t index = 0;
	size_t offset = 0;
	size_t i = 0;
	memset(dst, 0, len);
	for (i = 0; src[i]; i++) {
		unsigned char n = 0;
		for (; n < 32; n++) if (src[i] == BASE32_ALPHABET[n]) break;
		if (n == 32) continue;
		if (index <= 3) {
			index = (index + 5) % 8;
			if (index == 0) {
				dst[offset++] |= n;
				if (offset == len) break;
			} else {
				dst[offset] |= n << (8 - index);
			}
		} else {
			index = (index + 5) % 8;
			dst[offset++] |= (n >> index);
			if (offset == len) break;
			dst[offset] |= n << (8 - index);
		}
	}
}
