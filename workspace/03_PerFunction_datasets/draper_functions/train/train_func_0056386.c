a0alloc(size_t size, bool zero)
{

	if (malloc_init())
		return (NULL);

	if (size == 0)
		size = 1;

	if (size <= arena_maxclass)
		return (arena_malloc(arenas[0], size, zero, false));
	else
		return (huge_malloc(size, zero));
}
