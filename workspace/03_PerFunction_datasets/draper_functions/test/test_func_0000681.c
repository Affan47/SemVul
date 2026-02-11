copyfile(int src, int dest, size_t bufsize, off64_t *size, off64_t total_size)
{
	ssize_t n, m ;
	char * cpbuf;
	size_t count;
	off64_t total_bytes = 0;
	size_t off;

	if ( ( cpbuf = malloc(bufsize) ) == NULL ) {
		perror("malloc");
		return -1;
	}

	if( is_feedback_enabled) {
		hash_printing_accept_byte_count(progress_set, 0, total_size);
	}

	do{
		off = 0;
		do{
			n = dc_read(src, cpbuf + off, bufsize - off);
			if( n <=0 ) break;
			off += n;
		} while (off != bufsize );


		if (n < 0) {

			free(cpbuf);
			return -1;
		}

		if (off > 0) {
			count = 0;

			while ((count != off) && ((m = dc_write(dest, cpbuf+count, off-count)) > 0)) {
				total_bytes += (off64_t)m;
				count += m;
				if( is_feedback_enabled) {
					hash_printing_accept_byte_count(progress_set, total_bytes, total_size);
				}
			}

			if (m < 0) {

				free(cpbuf);
				return -1;
			}
		}
	} while (n != 0);

	if(size != NULL) {
		*size = total_bytes;
	}

	if( is_feedback_enabled) {
		hash_printing_accept_byte_count( progress_finished, 0, 0);
	}
	free(cpbuf);
	return 0;
}
