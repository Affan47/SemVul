base58_decode_check(const char *str, uint8_t *data, int datalen)
{
	if (datalen > 128) {
		return 0;
	}
	uint8_t d[datalen + 4];
	size_t res = datalen + 4;
	if (b58tobin(d, &res, str) != true) {
		return 0;
	}
	if (res != (size_t)datalen + 4) {
		return 0;
	}
	if (b58check(d, res, str) < 0) {
		return 0;
	}
	memcpy(data, d, datalen);
	return datalen;
}
