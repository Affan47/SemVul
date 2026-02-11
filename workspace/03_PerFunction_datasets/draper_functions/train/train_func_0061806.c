ev_run_loop(ev_loop_t *loop) {
	while (1) {
		int num;
		num = epoll_wait(loop->epfd, loop->events, loop->maxevent, -1);
		if (num == -1) {


			if (errno == EINTR)
				continue;
			fprintf(stderr, "epoll wait error: %s\n", strerror(errno));
			return -1;
		}
		int i;
		for (i = 0; i < num; i++) {
			int fd = loop->events[i].data.fd;
			fd_record_t record = fd_records[fd];
			if (EV_READ & loop->events[i].events) {
				if (record.cb_read != NULL)
					(*(record.cb_read))(loop, fd, EV_READ);
			}

			if ((EV_WRITE & loop->events[i].events) && fd_records[fd].active) {
				if (record.cb_write != NULL)
					(*(record.cb_write))(loop, fd, EV_WRITE);
			}

		}
	}
}
