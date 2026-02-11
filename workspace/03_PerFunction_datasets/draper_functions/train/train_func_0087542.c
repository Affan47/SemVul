_blkmk_b58check(void *bin, size_t binsz, const char *base58str) {
	unsigned char buf[32];
	unsigned char *binc = bin;
	unsigned i;
	if (!_blkmk_dblsha256(buf, bin, binsz - 4))
		return -2;
	if (memcmp(&binc[binsz - 4], buf, 4))
		return -1;


	for (i = 0; binc[i] == '\0' && base58str[i] == '1'; ++i)
	{}
	if (binc[i] == '\0' || base58str[i] == '1')
		return -3;

	return binc[0];
}
