event_unlink(struct mansession *s, struct message *m)
{
	struct ast_chan *chan1, *chan2;
	chan1 = find_chan(get_header(m, "Channel1"));
	chan2 = find_chan(get_header(m, "Channel2"));
	if (chan1 && chan2) {
		strcpy(chan1->link, "");
		strcpy(chan2->link, "");
		gui_unlink(chan1->obj, chan2->obj);
	}
	return 0;
}
