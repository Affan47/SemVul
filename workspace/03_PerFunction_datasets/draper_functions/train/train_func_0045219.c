bridge_channel_talking(struct ast_bridge *bridge, struct ast_bridge_channel *bridge_channel)
{
	struct ast_bridge_features *features = (bridge_channel->features ? bridge_channel->features : &bridge->features);

	if (features && features->talker_cb) {
		features->talker_cb(bridge, bridge_channel, features->talker_pvt_data);
	}
	ast_bridge_change_state(bridge_channel, AST_BRIDGE_CHANNEL_STATE_WAIT);
}
