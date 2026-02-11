close(int fd)
{
	static int (*func)(int);

	if (!func) {
		printf("w00t.. we're hooking close!\n");
		func = (int (*)(int)) dlsym(RTLD_NEXT, "close");
	}

	if (fd == _fd) {
		printf("close(%d) is called.. stopping ioctl dumps to /dev/fb0!\n", _fd);
		_fd = 0;
	}

	return func(fd);
}
