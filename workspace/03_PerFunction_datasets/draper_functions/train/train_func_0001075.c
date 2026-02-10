posix_memalign(void **memptr, size_t alignment, size_t size)
{


	if ((alignment & (alignment - 1))
	    || alignment % sizeof (void *))
		return EINVAL;

	void *ptr = memalign (alignment, size);
	if (ptr == NULL)
		return ENOMEM;
	*memptr = ptr;
	return 0;
}
