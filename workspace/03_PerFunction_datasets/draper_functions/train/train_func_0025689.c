part(char *chan, char *nick)
{
	channel_t *c = channel_find(chan);
	user_t *u = user_find_named(nick);

	if (!u || !c)
		return;
	if (!chanuser_find(c, u))
		return;
	if (me.connected)
		part_sts(c, u);
	chanuser_delete(c, u);
}
