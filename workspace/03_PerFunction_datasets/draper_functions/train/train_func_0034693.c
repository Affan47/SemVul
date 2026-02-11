mpd_startSearch(mpd_Connection *connection, int exact)
{
	if (connection->request) {
		strcpy(connection->errorStr, "search already in progress");
		connection->error = 1;
		return;
	}

	if (exact) {
		connection->request = strndup("find", text_buffer_size);
	} else {
		connection->request = strndup("search", text_buffer_size);
	}
}
