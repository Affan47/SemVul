fz_malloc(fz_context *ctx, unsigned int size)
{
	void *p;

	if (size == 0)
		return NULL;

	p = do_scavenging_malloc(ctx, size);
	if (!p)
		fz_throw(ctx, "malloc of %d bytes failed", size);
	return p;
}
