block_hash (gconstpointer v)
{
	const signed char *p = v;
	guint32 h = *p++;
	int i;

	for (i = 0; i < 256; i++)
		h = (h << 5) - h + *p++;

	return h;
}
