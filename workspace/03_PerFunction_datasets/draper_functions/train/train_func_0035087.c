force_timeout(dig_lookup_t *l, dig_query_t *query) {
	isc_event_t *event;

	debug("force_timeout ()");
	event = isc_event_allocate(mctx, query, ISC_TIMEREVENT_IDLE,
				   connect_timeout, l,
				   sizeof(isc_event_t));
	if (event == NULL) {
		fatal("isc_event_allocate: %s",
		      isc_result_totext(ISC_R_NOMEMORY));
	}
	isc_task_send(global_task, &event);


	if (l->timer != NULL)
		isc_timer_detach(&l->timer);
}
