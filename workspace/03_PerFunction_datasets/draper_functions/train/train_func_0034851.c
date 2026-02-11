string_input(char* buf, size_t max) {
	if (read_ptr >= write_ptr ) {
		return YY_NULL;
	} else if ( read_ptr + max > write_ptr ) {
		max = write_ptr - read_ptr;
	}

	memcpy(buf,read_ptr,max);
	read_ptr += max;

	return max;
}
