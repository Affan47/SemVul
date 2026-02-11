check_beep(struct agent_pvt *newlyavailable, int needlock)
{
	struct agent_pvt *p;
	int res=0;

	ast_debug(1, "Checking beep availability of '%s'\n", newlyavailable->agent);
	if (needlock)
		AST_LIST_LOCK(&agents);
	AST_LIST_TRAVERSE(&agents, p, list) {
		if (p == newlyavailable) {
			continue;
		}
		ast_mutex_lock(&p->lock);
		if (!p->abouttograb && p->pending && ((p->group && (newlyavailable->group & p->group)) || !strcmp(p->agent, newlyavailable->agent))) {
			ast_debug(1, "Call '%s' looks like a would-be winner for agent '%s'\n", ast_channel_name(p->owner), newlyavailable->agent);
			ast_mutex_unlock(&p->lock);
			break;
		}
		ast_mutex_unlock(&p->lock);
	}
	if (needlock)
		AST_LIST_UNLOCK(&agents);
	if (p) {
		ast_mutex_unlock(&newlyavailable->lock);
		ast_debug(3, "Playing beep, lang '%s'\n", ast_channel_language(newlyavailable->chan));
		res = ast_streamfile(newlyavailable->chan, beep, ast_channel_language(newlyavailable->chan));
		ast_debug(1, "Played beep, result '%d'\n", res);
		if (!res) {
			res = ast_waitstream(newlyavailable->chan, "");
			ast_debug(1, "Waited for stream, result '%d'\n", res);
		}
		ast_mutex_lock(&newlyavailable->lock);
	}
	return res;
}
