mpd_run_prio_id(struct mpd_connection *connection, int priority,
		unsigned id)
{
	return mpd_run_check(connection) &&
		mpd_send_prio_id(connection, priority, id) &&
		mpd_response_finish(connection);
}
