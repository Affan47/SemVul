kmem_realloc(const void *ptr, size_t newsize, size_t oldsize,
	     xfs_km_flags_t flags)
{
	void	*new;

	new = kmem_alloc(newsize, flags);
	if (ptr) {
		if (new)
			memcpy(new, ptr,
				((oldsize < newsize) ? oldsize : newsize));
		kmem_free(ptr);
	}
	return new;
}
