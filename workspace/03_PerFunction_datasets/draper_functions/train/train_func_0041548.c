event_wait(events_t *ev, int microseconds)
{
	struct timeval *t = NULL;

	if(microseconds != -1)
	{
		t 			= &ev->tv;
		t->tv_sec 	= 0;
		t->tv_usec 	= microseconds;
	}

	ev->set_read_copy 	= ev->set_read;
	ev->set_write_copy 	= ev->set_write;
	ev->set_error_copy 	= ev->set_error;


	ev->currfd = -1;

	ev->nevents = select(ev->max_fd + 1, &(ev->set_read_copy),
			&(ev->set_write_copy), &(ev->set_error_copy), t);


	if(ev->nevents == -1)
	{
		if(errno == EINTR)
			return 0;

		perror("event_wait():");
		return -1;
	}

	return ev->nevents;
}
