remove_banlike(user_t *source, channel_t *chan, int type, user_t *target)
{
	char change[MAX_BUF];
	int count = 0;
	mowgli_node_t *n, *tn;
	chanban_t *cb;

	if (type == 0)
		return 0;
	if (source == NULL || chan == NULL || target == NULL)
		return 0;

	for (n = next_matching_ban(chan, target, type, chan->bans.head); n != NULL; n = next_matching_ban(chan, target, type, tn))
	{
		tn = n->next;
		cb = n->data;

		snprintf(change, sizeof change, "-%c %s", cb->type, cb->mask);
		mode_sts(source->nick, chan, change);
		chanban_delete(cb);
		count++;
	}
	return count;
}
