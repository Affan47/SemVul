get_sha1_hex(const char *hex, unsigned char *sha1)
{
	int i;
	for (i = 0; i < 20; i++) {
		unsigned int val = (hexval(hex[0]) << 4) | hexval(hex[1]);
		if (val & ~0xff)
			return -1;
		*sha1++ = val;
		hex += 2;
	}
	return 0;
}
