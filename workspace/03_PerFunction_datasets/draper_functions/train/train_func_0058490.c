generic_wallchops(user_t *sender, channel_t *channel, const char *message)
{

	mowgli_node_t *n;
	chanuser_t *cu;

	MOWGLI_ITER_FOREACH(n, channel->members.head)
	{
		cu = (chanuser_t *)n->data;
		if (cu->user->server != me.me && cu->modes & CSTATUS_OP)
			notice(sender->nick, cu->user->nick, "[@%s] %s", channel->name, message);
	}
}
