arena_prof_promoted(const void *ptr, size_t size)
{
	arena_chunk_t *chunk;
	size_t pageind, binind;

	cassert(config_prof);
	assert(ptr != NULL);
	assert(CHUNK_ADDR2BASE(ptr) != ptr);
	assert(isalloc(ptr, false) == PAGE);
	assert(isalloc(ptr, true) == PAGE);
	assert(size <= SMALL_MAXCLASS);

	chunk = (arena_chunk_t *)CHUNK_ADDR2BASE(ptr);
	pageind = ((uintptr_t)ptr - (uintptr_t)chunk) >> LG_PAGE;
	binind = SMALL_SIZE2BIN(size);
	assert(binind < NBINS);
	arena_mapbits_large_binind_set(chunk, pageind, binind);

	assert(isalloc(ptr, false) == PAGE);
	assert(isalloc(ptr, true) == size);
}
