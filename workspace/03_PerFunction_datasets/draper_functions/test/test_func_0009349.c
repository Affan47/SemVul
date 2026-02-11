read_file(const char* filename)
{
	char* str;
	char buf[MAX_WELCOME_SIZE];
	int fd = open(filename, O_RDONLY);
	int ret;

	if (fd == -1)
		return NULL;

	ret = read(fd, buf, MAX_WELCOME_SIZE);
	close(fd);

	buf[ret > 0 ? ret : 0] = 0;
	str = strdup(buf);

	return str;
}
