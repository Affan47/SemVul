unparse_raw_text(char *buffer, uint8_t *p, uint64_t length)
{
	uint64_t i; unsigned char c;
	char *q = buffer;
	for (i=0; i<length; i++) {
		c = p[i];
		if (c < 32 || c > 127) c = '.';
		q += sprintf(q, "%c", c);
	}
	return q - buffer;
}
