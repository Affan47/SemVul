event_end_of_who(IRC_SERVER_REC *server, const char *data)
{
        SERVER_QUERY_REC *rec;
        GSList *tmp, *next;
	char *params, *channel, **channels;
        int failed, multiple;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 2, NULL, &channel);
	multiple = strchr(channel, ',') != NULL;
	channels = g_strsplit(channel, ",", -1);

        failed = FALSE;
	rec = server->chanqueries;
	for (tmp = rec->current_queries; tmp != NULL; tmp = next) {
		IRC_CHANNEL_REC *chanrec = tmp->data;

                next = tmp->next;
		if (strarray_find(channels, chanrec->name) == -1)
			continue;

		if (chanrec->ownnick->host == NULL && multiple &&
		    !server->one_endofwho) {


			failed = TRUE;
		} else {
			chanrec->wholist = TRUE;
			signal_emit("channel wholist", 1, chanrec);
			channel_got_query(chanrec, CHANNEL_QUERY_WHO);
		}
	}

	g_strfreev(channels);
	if (multiple)
		server->one_endofwho = TRUE;

	if (failed) {


                query_current_error(server);
	}

        g_free(params);
}
