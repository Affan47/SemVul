evutil_read_file(const char *filename, char **content_out, size_t *len_out,
    int is_binary)
{
	int fd, r;
	struct stat st;
	char *mem;
	size_t read_so_far=0;
	int mode = O_RDONLY;

	EVUTIL_ASSERT(content_out);
	EVUTIL_ASSERT(len_out);
	*content_out = NULL;
	*len_out = 0;

#ifdef O_BINARY
	if (is_binary)
		mode |= O_BINARY;
#endif

	fd = open(filename, mode);
	if (fd < 0)
		return -1;
	if (fstat(fd, &st)) {
		close(fd);
		return -2;
	}
	mem = mm_malloc(st.st_size + 1);
	if (!mem) {
		close(fd);
		return -2;
	}
	read_so_far = 0;
	while ((r = read(fd, mem+read_so_far, st.st_size - read_so_far)) > 0) {
		read_so_far += r;
		if (read_so_far >= st.st_size)
			break;
		EVUTIL_ASSERT(read_so_far < st.st_size);
	}
	if (r < 0) {
		close(fd);
		mm_free(mem);
		return -2;
	}
	mem[read_so_far] = 0;

	*len_out = read_so_far;
	*content_out = mem;
	return 0;
}
