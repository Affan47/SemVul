radius_event_init(CONF_SECTION *cs, int have_children)
{
	rad_listen_t *head = NULL;

	if (el) return 0;

	time(&fr_start_time);

	el = fr_event_list_create(event_status);
	if (!el) return 0;

	pl = fr_packet_list_create(0);
	if (!pl) return 0;

	request_num_counter = 0;

#ifdef WITH_PROXY
	if (mainconfig.proxy_requests) {


		proxy_list = fr_packet_list_create(1);
		if (!proxy_list) return 0;

#ifdef HAVE_PTHREAD_H
		if (pthread_mutex_init(&proxy_mutex, NULL) != 0) {
			radlog(L_ERR, "FATAL: Failed to initialize proxy mutex: %s",
			       strerror(errno));
			exit(1);
		}
#endif
	}
#endif

#ifdef HAVE_PTHREAD_H
	NO_SUCH_CHILD_PID = pthread_self();


	if (have_children && !check_config &&
	    (thread_pool_init(cs, &have_children) < 0)) {
		exit(1);
	}
#endif


	spawn_flag = have_children;

	if (check_config) {
		DEBUG("%s: #### Skipping IP addresses and Ports ####",
		       mainconfig.name);
		if (listen_init(cs, &head, spawn_flag) < 0) {
			fflush(NULL);
			exit(1);
		}
		return 1;
	}

#ifdef WITH_SELF_PIPE


	if (pipe(self_pipe) < 0) {
		radlog(L_ERR, "radiusd: Error opening internal pipe: %s",
		       strerror(errno));
		exit(1);
	}
	if (fcntl(self_pipe[0], F_SETFL, O_NONBLOCK | FD_CLOEXEC) < 0) {
		radlog(L_ERR, "radiusd: Error setting internal flags: %s",
		       strerror(errno));
		exit(1);
	}
	if (fcntl(self_pipe[1], F_SETFL, O_NONBLOCK | FD_CLOEXEC) < 0) {
		radlog(L_ERR, "radiusd: Error setting internal flags: %s",
		       strerror(errno));
		exit(1);
	}

	if (!fr_event_fd_insert(el, 0, self_pipe[0],
				  event_signal_handler, el)) {
		radlog(L_ERR, "Failed creating handler for signals");
		exit(1);
	}
#endif

       DEBUG("%s: #### Opening IP addresses and Ports ####",
	       mainconfig.name);


       if (listen_init(cs, &head, spawn_flag) < 0) {
		_exit(1);
	}

	mainconfig.listen = head;


	fr_suid_down_permanent();

	return 1;
}
