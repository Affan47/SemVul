h_calloc(size_t n, size_t len)
{
	void * ptr = halloc(0, len*=n);
	return ptr ? memset(ptr, 0, len) : NULL;
}
