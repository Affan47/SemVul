modes_type_a(IRC_CHANNEL_REC *channel, const char *setby, char type,
		  char mode, char *arg, GString *newmode)
{
	if (mode == 'b') {
		if (type == '+')
			banlist_add(channel, arg, setby, time(NULL));
		else
			banlist_remove(channel, arg, setby);
	}
}
