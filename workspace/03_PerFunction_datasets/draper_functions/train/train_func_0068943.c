copy(char *buf, size_t size, int offset, const char *src)
{
	size_t i, len;
	unsigned char c;


	while ((c = *src) != 0) {
		if (!crud(c))
			break;
		src++;
	}


	len = strlen(src);
	while (len > 0) {
		c = src[len-1];
		if (!crud(c))
			break;
		--len;
	}


	for (i = 0; i < len; i++) {
		c = *src++;
		switch (c) {
		case '\n': case '<': case '>':
			continue;
		}
		if (offset >= size)
			return size;
		buf[offset++] = c;
	}
	return offset;
}
