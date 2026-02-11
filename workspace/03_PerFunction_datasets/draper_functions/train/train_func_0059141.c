zend_mm_mem_mmap_anon_alloc(zend_mm_storage *storage, size_t size)
{
	zend_mm_segment *ret = (zend_mm_segment*)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (ret == MAP_FAILED) {
		ret = NULL;
	}
	return ret;
}
