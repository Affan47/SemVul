log_socket_event(ioa_socket_handle s, const char *msg, int error) {
	if(s && (error || (s->e && s->e->verbose))) {
		if(!msg)
			msg = "General socket event";
		turnsession_id id = 0;
		{
			ts_ur_super_session *ss = s->session;
			if (ss) {
				id = ss->id;
			} else{
				return;
			}
		}

		TURN_LOG_LEVEL ll = TURN_LOG_LEVEL_INFO;
		if(error)
			ll = TURN_LOG_LEVEL_ERROR;

		UNUSED_ARG(ll);

		{
			char sraddr[129]="\0";
			char sladdr[129]="\0";
			addr_to_string(&(s->remote_addr),(u08bits*)sraddr);
			addr_to_string(&(s->local_addr),(u08bits*)sladdr);

			if(EVUTIL_SOCKET_ERROR()) {
				TURN_LOG_FUNC(ll,"session %018llu: %s: %s (local %s, remote %s)\n",(unsigned long long)id,
											msg, evutil_socket_error_to_string(EVUTIL_SOCKET_ERROR()),
											sladdr,sraddr);
			} else {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,"session %018llu: %s (local %s, remote %s)\n",
						(unsigned long long)id,msg,sladdr,sraddr);
			}
		}
	}
}
