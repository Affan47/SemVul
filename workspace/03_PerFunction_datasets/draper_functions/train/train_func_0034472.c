get_hex_from_string(const char *buf, size_t buflen, unsigned *hex)
{
	size_t i;

	assert(hex != NULL);
	*hex = 0;
	for (i = 0; i < buflen && buf[i] != '\0'; ++i) {
		*hex <<= 4;
		if (isdigit(buf[i])) {
			*hex |= buf[i] - '0';
		} else if (buf[i] >= 'a' && buf[i] <= 'f') {
			*hex |= buf[i] - 'a' + 10;
		} else if (buf[i] >= 'A' && buf[i] <= 'F') {
			*hex |= buf[i] - 'A' + 10;
		} else {
			return 0;
		}
	}
	return i;
}
