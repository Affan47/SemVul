run_once(int num_pipes)
{
	int i;
	evutil_socket_t *cp;
	static struct timeval ts, te, tv_timeout;

	events = calloc(num_pipes, sizeof(struct event));
	pipes = calloc(num_pipes * 2, sizeof(evutil_socket_t));

	if (events == NULL || pipes == NULL) {
		perror("malloc");
		exit(1);
	}

	for (cp = pipes, i = 0; i < num_pipes; i++, cp += 2) {
		if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, cp) == -1) {
			perror("socketpair");
			exit(1);
		}
	}


	evutil_gettimeofday(&ts, NULL);


	evutil_timerclear(&tv_timeout);
	tv_timeout.tv_sec = 60;

	for (cp = pipes, i = 0; i < num_pipes; i++, cp += 2) {
		evutil_socket_t fd = i < num_pipes - 1 ? cp[3] : -1;
		event_set(&events[i], cp[0], EV_READ, read_cb,
		    (void *)(ev_intptr_t)fd);
		event_add(&events[i], &tv_timeout);
	}

	fired = 0;


	if (send(pipes[1], "e", 1, 0) < 0)
		perror("send");

	event_dispatch();

	evutil_gettimeofday(&te, NULL);
	evutil_timersub(&te, &ts, &te);

	for (cp = pipes, i = 0; i < num_pipes; i++, cp += 2) {
		event_del(&events[i]);
		close(cp[0]);
		close(cp[1]);
	}

	free(pipes);
	free(events);

	return (&te);
}
