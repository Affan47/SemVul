ast_dial_hangup(struct ast_dial *dial)
{
	struct ast_dial_channel *channel = NULL;

	if (!dial)
		return;

	AST_LIST_LOCK(&dial->channels);
	AST_LIST_TRAVERSE(&dial->channels, channel, list) {
		if (channel->owner) {
			ast_hangup(channel->owner);
			channel->owner = NULL;
		}
	}
	AST_LIST_UNLOCK(&dial->channels);

	return;
}
