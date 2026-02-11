crypt_safe_free(void *data)
{
	struct safe_allocation *alloc;

	if (!data)
		return;

	alloc = (struct safe_allocation *)
		((char *)data - offsetof(struct safe_allocation, data));

	memset(data, 0, alloc->size);

	alloc->size = 0x55aa55aa;
	free(alloc);
}
