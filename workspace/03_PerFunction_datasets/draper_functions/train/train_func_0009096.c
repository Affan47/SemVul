_php_stream_copy_to_mem(php_stream *src, char **buf, size_t maxlen, int persistent STREAMS_DC TSRMLS_DC)
{
	size_t ret = 0;
	char *ptr;
	size_t len = 0, max_len;
	int step = CHUNK_SIZE;
	int min_room = CHUNK_SIZE / 4;
	php_stream_statbuf ssbuf;

	if (maxlen == 0) {
		return 0;
	}

	if (maxlen == PHP_STREAM_COPY_ALL) {
		maxlen = 0;
	}

	if (maxlen > 0) {
		ptr = *buf = pemalloc_rel_orig(maxlen + 1, persistent);
		while ((len < maxlen) && !php_stream_eof(src)) {
			ret = php_stream_read(src, ptr, maxlen - len);
			len += ret;
			ptr += ret;
		}
		*ptr = '\0';
		return len;
	}


	if (php_stream_stat(src, &ssbuf) == 0 && ssbuf.sb.st_size > 0) {
		max_len = ssbuf.sb.st_size + step;
	} else {
		max_len = step;
	}

	ptr = *buf = pemalloc_rel_orig(max_len, persistent);

	while((ret = php_stream_read(src, ptr, max_len - len)))	{
		len += ret;
		if (len + min_room >= max_len) {
			*buf = perealloc_rel_orig(*buf, max_len + step, persistent);
			max_len += step;
			ptr = *buf + len;
		} else {
			ptr += ret;
		}
	}
	if (len) {
		*buf = perealloc_rel_orig(*buf, len + 1, persistent);
		(*buf)[len] = '\0';
	} else {
		pefree(*buf, persistent);
		*buf = NULL;
	}
	return len;
}
