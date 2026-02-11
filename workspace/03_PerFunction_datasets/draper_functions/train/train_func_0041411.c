mpd_recv_queue_change_brief(struct mpd_connection *connection,
			    unsigned *position_r, unsigned *id_r)
{
	struct mpd_pair *pair;

	pair = mpd_recv_pair_named(connection, "cpos");
	if (pair == NULL)
		return false;

	*position_r = atoi(pair->value);
	mpd_return_pair(connection, pair);

	pair = mpd_recv_pair_named(connection, "Id");
	if (pair == NULL) {
		mpd_return_pair(connection, pair);

		if (!mpd_error_is_defined(&connection->error)) {
			mpd_error_code(&connection->error,
				       MPD_ERROR_MALFORMED);
			mpd_error_message(&connection->error,
					  "No id received");
		}

		return false;
	}

	*id_r = atoi(pair->value);
	mpd_return_pair(connection, pair);

	return !mpd_error_is_defined(&connection->error);
}
