easypen_init(int fd, unsigned long *id, unsigned long *extra)
{
	char buf[256];


	write(fd, 0, 1);
	usleep(400000);


	if (write(fd, EP_PROMPT_MODE, 1) == -1)
		return -1;


	while (read(fd, buf, sizeof(buf)) == sizeof(buf));


	if (write(fd, EP_ABSOLUTE EP_STREAM_MODE EP_UPPER_ORIGIN, 3) == -1)
		return -1;

	return 0;
}
