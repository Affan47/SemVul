ast_bridge_unsuspend(struct ast_bridge *bridge, struct ast_channel *chan)
{
	struct ast_bridge_channel *bridge_channel;

	ao2_lock(bridge);

	if (!(bridge_channel = find_bridge_channel(bridge, chan))) {
		ao2_unlock(bridge);
		return -1;
	}

	bridge_channel_unsuspend(bridge, bridge_channel);

	ao2_unlock(bridge);

	return 0;
}
