find_bridge_channel(struct ast_bridge *bridge, struct ast_channel *chan)
{
	struct ast_bridge_channel *bridge_channel = NULL;

	AST_LIST_TRAVERSE(&bridge->channels, bridge_channel, entry) {
		if (bridge_channel->chan == chan) {
			break;
		}
	}

	return bridge_channel;
}
