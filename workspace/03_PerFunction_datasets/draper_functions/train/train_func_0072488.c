base_alloc(size_t size)
{
	void *ret;
	size_t csize;


	csize = CACHELINE_CEILING(size);

	malloc_mutex_lock(&base_mtx);

	if ((uintptr_t)base_next_addr + csize > (uintptr_t)base_past_addr) {
		if (base_pages_alloc(csize)) {
			malloc_mutex_unlock(&base_mtx);
			return (NULL);
		}
	}

	ret = base_next_addr;
	base_next_addr = (void *)((uintptr_t)base_next_addr + csize);
	malloc_mutex_unlock(&base_mtx);

	return (ret);
}
