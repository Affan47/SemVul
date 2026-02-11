zend_mm_mem_mmap_zero_init(void *params)
{
	if (zend_mm_dev_zero_fd != -1) {
		zend_mm_dev_zero_fd = open("/dev/zero", O_RDWR, S_IRUSR | S_IWUSR);
	}
	if (zend_mm_dev_zero_fd >= 0) {
		return malloc(sizeof(zend_mm_storage));
	} else {
		return NULL;
	}
}
