disconnect_other_sessions(WSPMachine *sm) {
	List *old_sessions;
	WAPEvent *disconnect;
	WSPMachine *sm2;
	long i;

	old_sessions = gwlist_search_all(session_machines, sm, same_client);
	if (old_sessions == NULL)
		return;

	for (i = 0; i < gwlist_len(old_sessions); i++) {
		sm2 = gwlist_get(old_sessions, i);
		if (sm2 != sm) {
			disconnect = wap_event_create(Disconnect_Event);
			handle_session_event(sm2, disconnect, NULL);
		}
	}

	gwlist_destroy(old_sessions, NULL);
}
