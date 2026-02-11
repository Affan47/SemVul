escape_size (char *src, size_t len)
{
	size_t sz;
	char c;
	int i;

	sz = 0;
	for (i = 0; i < len; i++) {
		c = src[i];
		switch (c) {
			case '&': sz += 5; break;
			case '\'': sz += 6; break;
			case '"': sz += 6; break;
			case '<': sz += 4; break;
			case '>': sz += 4; break;
			default: sz++; break;
		}
	}
	return sz;
}
