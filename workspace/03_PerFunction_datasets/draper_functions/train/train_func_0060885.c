setblocking(int fd) {
    long arg;
    if ((arg = fcntl(fd, F_GETFL, NULL)) < 0) {
	perror("fcntl(F_GETFL)");
	exit(1);
    }
    arg &= ~O_NONBLOCK;
    if (fcntl(fd, F_SETFL, arg) < 0) {
	perror("fcntl(F_SETFL)");
	exit(1);
    }
}
