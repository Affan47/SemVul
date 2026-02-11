event_topic_info(IRC_SERVER_REC *server, const char *data)
{
	const char *channel;
	char *params, *timestr, *bynick, *byhost, *topictime;

	g_return_if_fail(data != NULL);

	params = event_get_params(data, 4, NULL, &channel,
				  &bynick, &topictime);

        timestr = my_asctime((time_t) atol(topictime));

	byhost = strchr(bynick, '!');
	if (byhost != NULL)
		*byhost++ = '\0';

	channel = get_visible_target(server, channel);
	printformat(server, channel, MSGLEVEL_CRAP, IRCTXT_TOPIC_INFO,
		    bynick, timestr, byhost == NULL ? "" : byhost);
	g_free(timestr);
	g_free(params);
}
