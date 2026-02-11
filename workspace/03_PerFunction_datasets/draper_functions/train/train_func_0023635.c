_zend_mm_free_int(zend_mm_heap *heap, void *p ZEND_FILE_LINE_DC ZEND_FILE_LINE_ORIG_DC)
{
	zend_mm_block *mm_block;
	zend_mm_block *next_block;
	size_t size;

	if (!ZEND_MM_VALID_PTR(p)) {
		return;
	}

	mm_block = ZEND_MM_HEADER_OF(p);
	size = ZEND_MM_BLOCK_SIZE(mm_block);
	ZEND_MM_CHECK_PROTECTION(mm_block);

#if ZEND_DEBUG || ZEND_MM_HEAP_PROTECTION
	memset(ZEND_MM_DATA_OF(mm_block), 0x5a, mm_block->debug.size);
#endif

#if ZEND_MM_CACHE
	if (EXPECTED(ZEND_MM_SMALL_SIZE(size)) && EXPECTED(heap->cached < ZEND_MM_CACHE_SIZE)) {
		size_t index = ZEND_MM_BUCKET_INDEX(size);
		zend_mm_free_block **cache = &heap->cache[index];

		((zend_mm_free_block*)mm_block)->prev_free_block = *cache;
		*cache = (zend_mm_free_block*)mm_block;
		heap->cached += size;
		ZEND_MM_SET_MAGIC(mm_block, MEM_BLOCK_CACHED);
#if ZEND_MM_CACHE_STAT
		if (++heap->cache_stat[index].count > heap->cache_stat[index].max_count) {
			heap->cache_stat[index].max_count = heap->cache_stat[index].count;
		}
#endif
		return;
	}
#endif

	HANDLE_BLOCK_INTERRUPTIONS();

	heap->size -= size;

	next_block = ZEND_MM_BLOCK_AT(mm_block, size);
	if (ZEND_MM_IS_FREE_BLOCK(next_block)) {
		zend_mm_remove_from_free_list(heap, (zend_mm_free_block *) next_block);
		size += ZEND_MM_FREE_BLOCK_SIZE(next_block);
	}
	if (ZEND_MM_PREV_BLOCK_IS_FREE(mm_block)) {
		mm_block = ZEND_MM_PREV_BLOCK(mm_block);
		zend_mm_remove_from_free_list(heap, (zend_mm_free_block *) mm_block);
		size += ZEND_MM_FREE_BLOCK_SIZE(mm_block);
	}
	if (ZEND_MM_IS_FIRST_BLOCK(mm_block) &&
	    ZEND_MM_IS_GUARD_BLOCK(ZEND_MM_BLOCK_AT(mm_block, size))) {
		zend_mm_del_segment(heap, (zend_mm_segment *) ((char *)mm_block - ZEND_MM_ALIGNED_SEGMENT_SIZE));
	} else {
		ZEND_MM_BLOCK(mm_block, ZEND_MM_FREE_BLOCK, size);
		zend_mm_add_to_free_list(heap, (zend_mm_free_block *) mm_block);
	}
	HANDLE_UNBLOCK_INTERRUPTIONS();
}
