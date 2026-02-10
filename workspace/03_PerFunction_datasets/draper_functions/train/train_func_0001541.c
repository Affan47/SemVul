_php_stream_copy_to_stream_ex(php_stream *src, php_stream *dest, size_t maxlen, size_t *len STREAMS_DC TSRMLS_DC)
{
	char buf[CHUNK_SIZE];
	size_t readchunk;
	size_t haveread = 0;
	size_t didread;
	size_t dummy;
	php_stream_statbuf ssbuf;

	if (!len) {
		len = &dummy;
	}

	if (maxlen == 0) {
		*len = 0;
		return SUCCESS;
	}

	if (maxlen == PHP_STREAM_COPY_ALL) {
		maxlen = 0;
	}

	if (php_stream_stat(src, &ssbuf) == 0) {
		if (ssbuf.sb.st_size == 0
#ifdef S_ISREG
			&& S_ISREG(ssbuf.sb.st_mode)
#endif
		) {
			*len = 0;
			return SUCCESS;
		}
	}

	if (php_stream_mmap_possible(src)) {
		char *p;
		size_t mapped;

		p = php_stream_mmap_range(src, php_stream_tell(src), maxlen, PHP_STREAM_MAP_MODE_SHARED_READONLY, &mapped);

		if (p) {
			mapped = php_stream_write(dest, p, mapped);

			php_stream_mmap_unmap_ex(src, mapped);

			*len = mapped;


			if (mapped > 0) {
				return SUCCESS;
			}
			return FAILURE;
		}
	}

	while(1) {
		readchunk = sizeof(buf);

		if (maxlen && (maxlen - haveread) < readchunk) {
			readchunk = maxlen - haveread;
		}

		didread = php_stream_read(src, buf, readchunk);

		if (didread) {

			size_t didwrite, towrite;
			char *writeptr;

			towrite = didread;
			writeptr = buf;
			haveread += didread;

			while(towrite) {
				didwrite = php_stream_write(dest, writeptr, towrite);
				if (didwrite == 0) {
					*len = haveread - (didread - towrite);
					return FAILURE;
				}

				towrite -= didwrite;
				writeptr += didwrite;
			}
		} else {
			break;
		}

		if (maxlen - haveread == 0) {
			break;
		}
	}

	*len = haveread;


	if (haveread > 0 || src->eof) {
		return SUCCESS;
	}
	return FAILURE;
}
