get_visible_target(IRC_SERVER_REC *server, const char *target)
{
	IRC_CHANNEL_REC *channel;

	if (*target == '!') {


		channel = irc_channel_find(server, target);
		if (channel != NULL)
			return channel->visible_name;
	}

	return target;
}
