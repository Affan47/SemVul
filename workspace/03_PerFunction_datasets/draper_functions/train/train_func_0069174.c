agent_sendtext(struct ast_channel *ast, const char *text)
{
	struct agent_pvt *p = ast_channel_tech_pvt(ast);
	int res = -1;
	ast_mutex_lock(&p->lock);
	if (p->chan)
		res = ast_sendtext(p->chan, text);
	ast_mutex_unlock(&p->lock);
	return res;
}
