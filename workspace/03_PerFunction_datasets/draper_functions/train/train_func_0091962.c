agents_show(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	struct agent_pvt *p;
	char username[AST_MAX_BUF];
	char location[AST_MAX_BUF] = "";
	char talkingto[AST_MAX_BUF] = "";
	char music[AST_MAX_BUF];
	int count_agents = 0;
	int online_agents = 0;
	int offline_agents = 0;

	switch (cmd) {
	case CLI_INIT:
		e->command = "agent show";
		e->usage =
			"Usage: agent show\n"
			"       Provides summary information on agents.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 2)
		return CLI_SHOWUSAGE;

	AST_LIST_LOCK(&agents);
	AST_LIST_TRAVERSE(&agents, p, list) {
		struct ast_channel *owner;
		ast_mutex_lock(&p->lock);
		owner = agent_lock_owner(p);
		if (p->pending) {
			if (p->group)
				ast_cli(a->fd, "-- Pending call to group %d\n", powerof(p->group));
			else
				ast_cli(a->fd, "-- Pending call to agent %s\n", p->agent);
		} else {
			if (!ast_strlen_zero(p->name))
				snprintf(username, sizeof(username), "(%s) ", p->name);
			else
				username[0] = '\0';
			if (p->chan) {
				snprintf(location, sizeof(location), "logged in on %s", ast_channel_name(p->chan));
				if (owner && ast_bridged_channel(owner)) {
					snprintf(talkingto, sizeof(talkingto), " talking to %s", ast_channel_name(ast_bridged_channel(p->owner)));
				} else {
					strcpy(talkingto, " is idle");
				}
				online_agents++;
			} else {
				strcpy(location, "not logged in");
				talkingto[0] = '\0';
				offline_agents++;
			}
			if (!ast_strlen_zero(p->moh))
				snprintf(music, sizeof(music), " (musiconhold is '%s')", p->moh);
			ast_cli(a->fd, "%-12.12s %s%s%s%s\n", p->agent,
				username, location, talkingto, music);
			count_agents++;
		}

		if (owner) {
			ast_channel_unlock(owner);
			owner = ast_channel_unref(owner);
		}
		ast_mutex_unlock(&p->lock);
	}
	AST_LIST_UNLOCK(&agents);
	if ( !count_agents )
		ast_cli(a->fd, "No Agents are configured in %s\n",config);
	else
		ast_cli(a->fd, "%d agents configured [%d online , %d offline]\n",count_agents, online_agents, offline_agents);
	ast_cli(a->fd, "\n");

	return CLI_SUCCESS;
}
