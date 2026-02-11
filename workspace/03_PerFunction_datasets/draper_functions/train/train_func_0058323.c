agent_bridgedchannel(struct ast_channel *chan, struct ast_channel *bridge)
{
	struct agent_pvt *p = ast_channel_tech_pvt(bridge);
	struct ast_channel *ret = NULL;

	if (p) {
		if (chan == p->chan)
			ret = ast_channel_internal_bridged_channel(bridge);
		else if (chan == ast_channel_internal_bridged_channel(bridge))
			ret = p->chan;
	}

	ast_debug(1, "Asked for bridged channel on '%s'/'%s', returning '%s'\n", ast_channel_name(chan), ast_channel_name(bridge), ret ? ast_channel_name(ret) : "<none>");
	return ret;
}
