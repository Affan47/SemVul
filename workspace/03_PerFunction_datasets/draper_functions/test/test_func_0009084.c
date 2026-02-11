agent_digit_begin(struct ast_channel *ast, char digit)
{
	struct agent_pvt *p = ast_channel_tech_pvt(ast);
	ast_mutex_lock(&p->lock);
	if (p->chan) {
		ast_senddigit_begin(p->chan, digit);
	}
	ast_mutex_unlock(&p->lock);
	return 0;
}
