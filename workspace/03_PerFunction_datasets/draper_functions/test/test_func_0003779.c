bin_to_hex_dup(const unsigned char *src, int srclen)
{
	int i;
	char *buf, *hex;


	buf = kmalloc((srclen * 2) + 1, GFP_KERNEL);
	if (!buf)
		return buf;

	hex = buf;
	for (i = 0; i < srclen; i++) {
		sprintf(hex, "%2.2x", *src++);
		hex += 2;
	}
	return buf;
}
