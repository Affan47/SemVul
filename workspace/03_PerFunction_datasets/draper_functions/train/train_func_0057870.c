blob_rindex(blob_t *b, const void *buf, int len)
{
	int i;

	for (i = b->end - len; i >= 0; i--) {
		if (memcmp(b->base + i, buf, len) == 0)
			return (i);
	}
	return (-1);
}
