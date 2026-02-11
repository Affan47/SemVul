chanban_find(channel_t *chan, const char *mask, int type)
{
	chanban_t *c;
	mowgli_node_t *n;

	MOWGLI_ITER_FOREACH(n, chan->bans.head)
	{
		c = n->data;

		if (c->type == type && !irccasecmp(c->mask, mask))
			return c;
	}

	return NULL;
}
