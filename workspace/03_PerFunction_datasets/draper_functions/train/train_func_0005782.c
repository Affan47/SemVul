belkin_std_open_tty(const char *device) {
	int fd;
	struct termios tios;
	struct flock flock;
	char buf[128];
	int r;


	fd = open(device, O_RDWR | O_NONBLOCK);
	if (fd == -1) {
		return -1;
	}


	memset(&tios, 0, sizeof(tios));
	tios.c_cflag = B2400 | CS8 | CREAD | HUPCL | CLOCAL;
	tios.c_cc[VMIN] = 1;
	tios.c_cc[VTIME] = 0;
	r = tcsetattr(fd, TCSANOW, &tios);
	if (r == -1) {
		close(fd);
		return -1;
	}


	ser_set_dtr(upsfd, 0);
	ser_set_rts(upsfd, 1);


	r = ser_flush_io(fd);
	if (r == -1) {
		close(fd);
		return -1;
	}


	memset(&flock, 0, sizeof(flock));
	flock.l_type = F_RDLCK;
	r = fcntl(fd, F_SETLK, &flock);
	if (r == -1) {
		close(fd);
		return -1;
	}


	usleep(1000000);


	r = tcflush(fd, TCIFLUSH);
	if (r == -1) {
		close(fd);
		return -1;
	}

	r = read(fd, buf, 127);
	if (r == -1 && errno != EAGAIN) {
		close(fd);
		return -1;
	}


	return fd;
}
