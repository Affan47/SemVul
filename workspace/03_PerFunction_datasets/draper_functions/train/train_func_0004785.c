tdb_convert(void *buf, uint32_t size)
{
	uint32_t i;
	unsigned char *p = buf, tmp;

	for (i = 0; i < size; i += 4) {
		tmp = p[i];
		p[i] = p[i+3];
		p[i+3] = tmp;
		tmp = p[i+1];
		p[i+1] = p[i+2];
		p[i+2] = tmp;
	}
	return buf;
}
