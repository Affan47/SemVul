remove(int fd) {
	int r = epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
	always_assert(r == 0);
    }
