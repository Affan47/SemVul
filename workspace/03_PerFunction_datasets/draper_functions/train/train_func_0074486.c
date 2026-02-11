print_hex_only (len, data, limit, buf)
	unsigned len;
	const u_int8_t *data;
	unsigned limit;
	char *buf;
{
	unsigned i;

	if ((buf == NULL) || (limit < 3))
		return;

	for (i = 0; (i < limit / 3) && (i < len); i++) {
		sprintf(&buf[i*3], "%02x:", data[i]);
	}
	buf[(i * 3) - 1] = 0;
	return;
}
