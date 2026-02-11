_talloc_zero_array(const void *ctx, size_t el_size, unsigned count, const char *name)
{
	void *p;

	if (count >= MAX_TALLOC_SIZE/el_size) {
		return NULL;
	}
	p = _talloc_zero(ctx, el_size * count, name);
	return p;
}
