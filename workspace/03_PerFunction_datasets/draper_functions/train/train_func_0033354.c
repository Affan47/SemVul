ast_bridge_join(struct ast_bridge *bridge,
	struct ast_channel *chan,
	struct ast_channel *swap,
	struct ast_bridge_features *features,
	struct ast_bridge_tech_optimizations *tech_args)
{
	struct ast_bridge_channel *bridge_channel = bridge_channel_alloc(bridge);
	enum ast_bridge_channel_state state = AST_BRIDGE_CHANNEL_STATE_HANGUP;

	if (!bridge_channel) {
		return state;
	}
	if (tech_args) {
		memcpy(&bridge_channel->tech_args, tech_args, sizeof(bridge_channel->tech_args));
	}


	bridge_channel->chan = chan;
	bridge_channel->swap = swap;
	bridge_channel->features = features;

	state = bridge_channel_join(bridge_channel);


	ao2_lock(bridge_channel);
	bridge_channel->chan = NULL;
	bridge_channel->swap = NULL;
	bridge_channel->features = NULL;
	ao2_unlock(bridge_channel);

	ao2_ref(bridge_channel, -1);

	return state;
}
