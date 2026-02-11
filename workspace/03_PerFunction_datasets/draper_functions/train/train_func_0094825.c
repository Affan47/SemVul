os_file_set_size(

	const char*	name,

	os_file_t	file,
	ulint		size,

	ulint		size_high)
{
	ib_int64_t	current_size;
	ib_int64_t	desired_size;
	ibool		ret;
	byte*		buf;
	byte*		buf2;
	ulint		buf_size;

	ut_a(size == (size & 0xFFFFFFFF));

	current_size = 0;
	desired_size = (ib_int64_t)size + (((ib_int64_t)size_high) << 32);


	buf_size = ut_min(64, (ulint) (desired_size / UNIV_PAGE_SIZE))
		* UNIV_PAGE_SIZE;
	buf2 = ut_malloc(buf_size + UNIV_PAGE_SIZE);


	buf = ut_align(buf2, UNIV_PAGE_SIZE);


	memset(buf, 0, buf_size);

	if (desired_size >= (ib_int64_t)(100 * 1024 * 1024)) {

		fprintf(stderr, "InnoDB: Progress in MB:");
	}

	while (current_size < desired_size) {
		ulint	n_bytes;

		if (desired_size - current_size < (ib_int64_t) buf_size) {
			n_bytes = (ulint) (desired_size - current_size);
		} else {
			n_bytes = buf_size;
		}

		ret = os_file_write(name, file, buf,
				    (ulint)(current_size & 0xFFFFFFFF),
				    (ulint)(current_size >> 32),
				    n_bytes);
		if (!ret) {
			ut_free(buf2);
			goto error_handling;
		}


		if ((ib_int64_t) (current_size + n_bytes) / (ib_int64_t)(100 * 1024 * 1024)
		    != current_size / (ib_int64_t)(100 * 1024 * 1024)) {

			fprintf(stderr, " %lu00",
				(ulong) ((current_size + n_bytes)
					 / (ib_int64_t)(100 * 1024 * 1024)));
		}

		current_size += n_bytes;
	}

	if (desired_size >= (ib_int64_t)(100 * 1024 * 1024)) {

		fprintf(stderr, "\n");
	}

	ut_free(buf2);

	ret = os_file_flush(file);

	if (ret) {
		return(TRUE);
	}

error_handling:
	return(FALSE);
}
