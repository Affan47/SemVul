blob_register_alloc(size_t size, void *(bmalloc)(size_t),
    void (*bfree)(void *), void *(*brealloc)(void *, size_t))
{
	bl_size = size;
	if (bmalloc != NULL)
		bl_malloc = bmalloc;
	if (bfree != NULL)
		bl_free = bfree;
	if (brealloc != NULL)
		bl_realloc = brealloc;
	return (0);
}
