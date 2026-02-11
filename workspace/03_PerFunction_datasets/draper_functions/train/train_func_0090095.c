__fill_random_buf(void *buf, unsigned int len, unsigned long seed)
{
	void *ptr = buf;

	while (len) {
		int this_len;

		if (len >= sizeof(int64_t)) {
			*((int64_t *) ptr) = seed;
			this_len = sizeof(int64_t);
		} else if (len >= sizeof(int32_t)) {
			*((int32_t *) ptr) = seed;
			this_len = sizeof(int32_t);
		} else if (len >= sizeof(int16_t)) {
			*((int16_t *) ptr) = seed;
			this_len = sizeof(int16_t);
		} else {
			*((int8_t *) ptr) = seed;
			this_len = sizeof(int8_t);
		}
		ptr += this_len;
		len -= this_len;
		seed *= GOLDEN_RATIO_PRIME;
		seed >>= 3;
	}
}
