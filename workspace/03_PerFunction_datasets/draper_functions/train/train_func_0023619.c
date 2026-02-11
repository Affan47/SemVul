mpd_command_list_begin(struct mpd_connection *connection, bool discrete_ok)
{
	bool success;

	assert(connection != NULL);

	if (connection->sending_command_list) {
		mpd_error_code(&connection->error, MPD_ERROR_STATE);
		mpd_error_message(&connection->error,
				  "already in command list mode");
		return false;
	}

	success = mpd_send_command2(connection,
				    discrete_ok
				    ? "command_list_ok_begin"
				    : "command_list_begin");
	if (!success)
		return false;

	connection->sending_command_list = true;
	connection->sending_command_list_ok = discrete_ok;
	connection->command_list_remaining = 0;
	connection->discrete_finished = false;

	return true;
}
