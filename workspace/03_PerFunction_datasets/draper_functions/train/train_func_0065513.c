fdmap(int fd) {
	int i = defcount;
	while (--i >= 0) {
		Defer *defer = &deftab[i];
		if (fd == defer->userfd) {
			fd = defer->realfd;
			if (fd == -1)
				return -1;
		}
	}
	return fd;
}
