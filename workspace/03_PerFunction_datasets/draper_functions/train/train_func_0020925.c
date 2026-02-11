chirp_alloc_putstream(const char *path, struct link * l, time_t stoptime)
{
	INT64_T fd, result, actual, total = 0;
	int buffer_size = 65536;
	char *buffer;

	fd = chirp_alloc_open(path, O_CREAT | O_TRUNC | O_WRONLY, 0700);
	if(fd < 0)
		return fd;

	link_putliteral(l, "0\n", stoptime);

	buffer = malloc(buffer_size);

	while(1) {
		result = link_read(l, buffer, buffer_size, stoptime);
		if(result <= 0)
			break;

		actual = chirp_alloc_pwrite(fd, buffer, result, total);
		if(actual != result)
			break;

		total += actual;
	}

	free(buffer);

	chirp_alloc_close(fd);

	return total;
}
