link(int fd, DispatcherMask mask, IOHandler* handler) {
    if (fd < 0 || fd >= NOFILE) {
	abort();
    }
    attach(fd, mask, handler);
}
