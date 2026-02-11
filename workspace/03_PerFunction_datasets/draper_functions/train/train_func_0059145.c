xcalloc_core(size_t n, size_t s, const char *func)
{
	unsigned char *x;
	x = (unsigned char*)calloc(n, s);
	if (x == 0) {
		fprintf(stderr, "[E::%s] Fail to allocate %ld bytes of memory.\n", func, s * n);
		return 0;
	}
	return (void*)x;
}
