misc_alloc(char *file, int line, size_t len)
{
	void *ptr;

	if (file == NULL)
		file = "[unknown file]";

	if (len == 0)
		misc_die(file, line, "misc_alloc: ?len?");

	if ((ptr = malloc(len)) == NULL)
		misc_die(file, line, "out of memory");

#if defined(COMPILE_DEBUG)
	debug(4, "alloc %u (%.*s:%d): %p",
		(unsigned) len, MAX_PATH_SIZE, file, line, ptr);
#endif

	memset(ptr, 0, len);
	return ptr;
}
