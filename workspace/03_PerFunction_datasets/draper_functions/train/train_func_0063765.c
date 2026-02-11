_php_stream_passthru(php_stream * stream STREAMS_DC TSRMLS_DC)
{
	size_t bcount = 0;
	char buf[8192];
	int b;

	if (php_stream_mmap_possible(stream)) {
		char *p;
		size_t mapped;

		p = php_stream_mmap_range(stream, php_stream_tell(stream), PHP_STREAM_MMAP_ALL, PHP_STREAM_MAP_MODE_SHARED_READONLY, &mapped);

		if (p) {
			PHPWRITE(p, mapped);

			php_stream_mmap_unmap_ex(stream, mapped);

			return mapped;
		}
	}

	while ((b = php_stream_read(stream, buf, sizeof(buf))) > 0) {
		PHPWRITE(buf, b);
		bcount += b;
	}

	return bcount;
}
