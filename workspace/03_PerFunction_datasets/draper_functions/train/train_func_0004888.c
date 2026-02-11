do_loop(struct timeval *wait)
{
	int ret;
	struct timeval tv;
	fd_set rfd, wfd;
	bool something_done = FALSE;

	if (EVENT_check_post())
		something_done = TRUE;

	#ifdef DEBUG_TIMER
	fprintf(stderr, "\ndo_loop: now = %.7g: select (%d)\n", time_to_double(time_now()), something_done);
	#endif

	if (get_timeout(wait, &tv))
		ret = do_select(&rfd, &wfd, NULL);
	else
	{
		ret = do_select(&rfd, &wfd, &tv);
		something_done = TRUE;
	}

	if (ret < 0 && errno != EINTR)
		THROW_SYSTEM(errno, NULL);

	#ifdef DEBUG_TIMER
	fprintf(stderr, "do_loop: now = %.7g: timers (%d)\n", time_to_double(time_now()), something_done);
	#endif

	raise_timers();

	#ifdef DEBUG_TIMER
	fprintf(stderr, "do_loop: now = %.7g: callbacks\n", time_to_double(time_now()));
	#endif

	if (ret > 0)
	{
		raise_callback(&rfd, &wfd);
		something_done = TRUE;
	}
	else if (ret < 0)
	{
		something_done = TRUE;
	}


	return something_done;
}
