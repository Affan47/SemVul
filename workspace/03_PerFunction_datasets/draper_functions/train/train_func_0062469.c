base64_decode(const char *str, unsigned char *buf, size_t size)
{
	unsigned int n;
	size_t i, j, actual = 0;

	for (i = 0; *str && *str != '='; ) {
		n =  base64_map(&str) << 18;
		n += base64_map(&str) << 12;
		n += base64_map(&str) << 6;
		n += base64_map(&str);

		if (i < size)
			buf[i++] = (n >> 16) & 255;
		if (i < size)
			buf[i++] = (n >> 8) & 255;
		if (i < size)
			buf[i++] = n & 255;

		actual += 3;
	}


	for (j = 0; j < 3 && str[j] == '='; j ++)
		actual --;

	return actual;
}
