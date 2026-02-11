do_comm_select(int msec)
{
    int i;
    int num, saved_errno;

    if (epoll_fds == 0) {
	assert(shutting_down);
	return COMM_SHUTDOWN;
    }
    statCounter.syscalls.polls++;
    num = epoll_wait(kdpfd, events, MAX_EVENTS, msec);
    saved_errno = errno;
    getCurrentTime();
    debug(5, 5) ("do_comm_select: %d fds ready\n", num);
    if (num < 0) {
	if (ignoreErrno(saved_errno))
	    return COMM_OK;

	debug(5, 1) ("comm_select: epoll failure: %s\n", xstrerror());
	return COMM_ERROR;
    }
    statHistCount(&statCounter.select_fds_hist, num);

    if (num == 0)
	return COMM_TIMEOUT;

    for (i = 0; i < num; i++) {
	comm_call_handlers(events[i].data.fd, events[i].events & ~EPOLLOUT, events[i].events & ~EPOLLIN);
    }

    return COMM_OK;
}
