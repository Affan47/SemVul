agents_data_provider_get(const struct ast_data_search *search,
	struct ast_data *data_root)
{
	struct agent_pvt *p;
	struct ast_data *data_agent, *data_channel, *data_talkingto;

	AST_LIST_LOCK(&agents);
	AST_LIST_TRAVERSE(&agents, p, list) {
		struct ast_channel *owner;

		data_agent = ast_data_add_node(data_root, "agent");
		if (!data_agent) {
			continue;
		}

		ast_mutex_lock(&p->lock);
		owner = agent_lock_owner(p);

		if (!(p->pending)) {
			ast_data_add_str(data_agent, "id", p->agent);
			ast_data_add_structure(agent_pvt, data_agent, p);

			ast_data_add_bool(data_agent, "logged", p->chan ? 1 : 0);
			if (p->chan) {
				data_channel = ast_data_add_node(data_agent, "loggedon");
				if (!data_channel) {
					ast_mutex_unlock(&p->lock);
					ast_data_remove_node(data_root, data_agent);
					if (owner) {
						ast_channel_unlock(owner);
						owner = ast_channel_unref(owner);
					}
					continue;
				}
				ast_channel_data_add_structure(data_channel, p->chan, 0);
				if (owner && ast_bridged_channel(owner)) {
					data_talkingto = ast_data_add_node(data_agent, "talkingto");
					if (!data_talkingto) {
						ast_mutex_unlock(&p->lock);
						ast_data_remove_node(data_root, data_agent);
						if (owner) {
							ast_channel_unlock(owner);
							owner = ast_channel_unref(owner);
						}
						continue;
					}
					ast_channel_data_add_structure(data_talkingto, ast_bridged_channel(owner), 0);
				}
			} else {
				ast_data_add_node(data_agent, "talkingto");
				ast_data_add_node(data_agent, "loggedon");
			}
			ast_data_add_str(data_agent, "musiconhold", p->moh);
		}

		if (owner) {
			ast_channel_unlock(owner);
			owner = ast_channel_unref(owner);
		}

		ast_mutex_unlock(&p->lock);


		if (!ast_data_search_match(search, data_agent)) {
			ast_data_remove_node(data_root, data_agent);
		}
	}
	AST_LIST_UNLOCK(&agents);

	return 0;
}
