find_relative_dial_channel(struct ast_dial *dial, struct ast_channel *owner)
{
	struct ast_dial_channel *channel = NULL;

	AST_LIST_LOCK(&dial->channels);
	AST_LIST_TRAVERSE(&dial->channels, channel, list) {
		if (channel->owner == owner)
			break;
	}
	AST_LIST_UNLOCK(&dial->channels);

	return channel;
}
