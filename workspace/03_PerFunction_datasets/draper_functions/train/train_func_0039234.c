multiplexed_bridge_write(struct ast_bridge *bridge, struct ast_bridge_channel *bridge_channel, struct ast_frame *frame)
{
	struct ast_bridge_channel *other;

	if (AST_LIST_FIRST(&bridge->channels) == AST_LIST_LAST(&bridge->channels)) {
		return AST_BRIDGE_WRITE_FAILED;
	}

	if (!(other = (AST_LIST_FIRST(&bridge->channels) == bridge_channel ? AST_LIST_LAST(&bridge->channels) : AST_LIST_FIRST(&bridge->channels)))) {
		return AST_BRIDGE_WRITE_FAILED;
	}

	if (other->state == AST_BRIDGE_CHANNEL_STATE_WAIT) {
		ast_write(other->chan, frame);
	}

	return AST_BRIDGE_WRITE_SUCCESS;
}
