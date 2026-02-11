blob_index(blob_t *b, const void *buf, int len)
{
	int i;

	for (i = b->off; i <= b->end - len; i++) {
		if (memcmp(b->base + i, buf, len) == 0)
			return (i);
	}
	return (-1);
}
