event_process(const struct timespec *timeout)
{
    int i, j;
    struct pollfd *fds = malloc(sizeof(struct pollfd) * event_count);
    for (i = 0, j = 0; i < event_count; i++) {
	events[i].fds_id = -1;
	if (events[i].active) {
	    events[i].fds_id = j;
	    fds[j].events = 0;
	    fds[j].fd = events[i].fd;
	    if (events[i].read) {
		fds[j].events |= POLLIN;
	    }
	    if (events[i].write) {
		fds[j].events |= POLLOUT;
	    }
	    j++;
	}
    }
#if (__GLIBC__ >= 2 && __GLIBC_MINOR__ >= 4)
    int ready = ppoll(fds, j, timeout, NULL);
#else
    int ready = poll(fds, j, timeout->tv_sec * 1000 + timeout->tv_nsec / 1000000);
#endif

    if (ready > 0) {

	for (i = 0, j = 0; i < event_count; i++) {
	    if (events[i].fds_id != j) {
		continue;
	    }
	    if (fds[j].revents) {
		int flags = 0;
		if (fds[j].revents & POLLIN) {
		    flags |= EVENT_READ;
		}
		if (fds[j].revents & POLLOUT) {
		    flags |= EVENT_WRITE;
		}
		if (fds[j].revents & POLLHUP) {
		    flags |= EVENT_HUP;
		}
		if (fds[j].revents & POLLERR) {
		    flags |= EVENT_ERR;
		}
		events[i].callback(flags, events[i].data);

	    }
	    j++;
	}
    }
    free(fds);
    return 0;

}
