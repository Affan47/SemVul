mpd_parse_welcome(struct mpd_connection *connection, const char *output)
{
	const char *tmp;
	char * test;

	if (strncmp(output,MPD_WELCOME_MESSAGE,strlen(MPD_WELCOME_MESSAGE))) {
		mpd_error_code(&connection->error, MPD_ERROR_MALFORMED);
		mpd_error_message(&connection->error,
				  "Malformed connect message received");
		return false;
	}

	tmp = &output[strlen(MPD_WELCOME_MESSAGE)];
	connection->version[0] = strtol(tmp, &test, 10);
	if (test == tmp) {
		mpd_error_code(&connection->error, MPD_ERROR_MALFORMED);
		mpd_error_message(&connection->error,
				  "Malformed version number in connect message");
		return false;
	}

	if (*test == '.') {
		connection->version[1] = strtol(test + 1, &test, 10);
		if (*test == '.')
			connection->version[2] = strtol(test + 1, &test, 10);
		else
			connection->version[2] = 0;
	} else {
		connection->version[1] = 0;
		connection->version[2] = 0;
	}

	return true;
}
