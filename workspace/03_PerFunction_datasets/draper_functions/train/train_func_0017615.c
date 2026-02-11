fz_malloc_array(fz_context *ctx, unsigned int count, unsigned int size)
{
	void *p;

	if (count == 0 || size == 0)
		return 0;

	if (count > UINT_MAX / size)
		fz_throw(ctx, "malloc of array (%d x %d bytes) failed (integer overflow)", count, size);

	p = do_scavenging_malloc(ctx, count * size);
	if (!p)
		fz_throw(ctx, "malloc of array (%d x %d bytes) failed", count, size);
	return p;
}
