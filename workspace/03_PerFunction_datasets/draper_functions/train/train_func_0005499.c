unlink(int fd) {
    if (fd < 0 || fd >= NOFILE) {
	abort();
    }
    detach(fd);
}
