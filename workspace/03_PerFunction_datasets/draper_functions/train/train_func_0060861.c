xrealloc(void* ptr, size_t size)
{
	void* mem;

	if (size < 1)
		size = 1;

	mem = realloc(ptr, size);

	if (mem == NULL)
		perror("xrealloc");

	return mem;
}
