http_connect_thread(thread_t * thread)
{
	checker_t *checker = THREAD_ARG(thread);
	http_checker_t *http_get_check = CHECKER_ARG(checker);
	http_t *http = HTTP_ARG(http_get_check);
	conn_opts_t *co = checker->co;
	url_t *fetched_url;
	enum connect_result status;
	int fd;


	if (!CHECKER_ENABLED(checker)) {
		thread_add_timer(thread->master, http_connect_thread, checker,
				 checker->vs->delay_loop);
		return 0;
	}


	fetched_url = fetch_next_url(http_get_check);

	if (!fetched_url) {


		if (!svr_checker_up(checker->id, checker->rs)) {
			log_message(LOG_INFO, "Remote Web server %s succeed on service."
					    , FMT_HTTP_RS(checker));
			smtp_alert(checker->rs, NULL, NULL, "UP",
				   "=> CHECK succeed on service <=");
			update_svr_checker_state(UP, checker->id
						   , checker->vs
						   , checker->rs);
		}
		http->req = NULL;
		return epilog(thread, 1, 0, 0) + 1;
	}


	if ((fd = socket(co->dst.ss_family, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		log_message(LOG_INFO, "WEB connection fail to create socket. Rescheduling.");
		thread_add_timer(thread->master, http_connect_thread, checker,
				checker->vs->delay_loop);

		return 0;
	}

	status = tcp_bind_connect(fd, co);


	if(tcp_connection_state(fd, status, thread, http_check_thread,
			co->connection_to)) {
		close(fd);
		log_message(LOG_INFO, "WEB socket bind failed. Rescheduling");
		thread_add_timer(thread->master, http_connect_thread, checker,
				checker->vs->delay_loop);
	}

	return 0;
}
