event_newchannel(struct mansession *s, struct message *m)
{
	struct ast_chan *chan;
	char tmp[256];
	chan = find_chan(get_header(m, "Channel"));
	strncpy(chan->state, get_header(m, "State"), sizeof(chan->state) - 1);
	strncpy(chan->callerid, get_header(m, "Callerid"), sizeof(chan->callerid) - 1);
	update_channel(chan);
	if (strlen(chan->callerid))
		snprintf(tmp, sizeof(tmp), "New channel %s from %s", chan->name, chan->callerid);
	else
		snprintf(tmp, sizeof(tmp), "New channel %s", chan->name);
	gui_status(tmp);
	return 0;
}
