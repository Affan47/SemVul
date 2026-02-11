lapack_malloc (size_t sz)
{
    void *mem = NULL;

    if (sz > lapack_mem_sz) {
	void *chunk = realloc(lapack_mem_chunk, sz);

	if (chunk != NULL) {
	    lapack_mem_chunk = mem = chunk;
	    lapack_mem_sz = sz;
	}
    } else {
	mem = lapack_mem_chunk;
    }

    return mem;
}
