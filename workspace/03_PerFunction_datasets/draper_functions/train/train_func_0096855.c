ev_timer_init(ev_loop_t *loop, int capacity) {
	loop->heap = (ev_timer_t**)malloc((capacity + 1)*sizeof(ev_timer_t*));
	if (loop->heap == NULL) {
		fprintf(stderr, "ERROR: no enough memory!\n");
		return -1;
	}
	int i;
	for (i = 0; i <= capacity; i++) {
		loop->heap[i] = NULL;
	}
	loop->heap_size = 0;
	loop->heap_capacity = capacity;


	if ((loop->timer_fd = timerfd_create(CLOCK_MONOTONIC, 0)) < 0) {
		fprintf(stderr, "ERROR: init timerfd error\n");
		return -1;
	}

	struct itimerspec newValue;
	bzero(&newValue, sizeof(newValue));
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 0;
	newValue.it_value = ts;
	if (timerfd_settime(loop->timer_fd, 0, &newValue, NULL) != 0) {
		fprintf(stderr, "ERROR: timerfd_settime error: %s\n", strerror(errno));
		return -1;
	}
	return ev_io_register(loop, loop->timer_fd, EV_READ, cb_check_timer, NULL);
}
