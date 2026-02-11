crealloc(void *ptr, size_t new_size)
{
	ptr = realloc(ptr, new_size);
	if (new_size)
		check(ptr);
	return ptr;
}
