bridge_call(struct ast_channel *ast, const char *dest, int timeout)
{
	struct bridge_pvt *p = ast_channel_tech_pvt(ast);


	if (!ast_channel_internal_bridge(ast)) {
		return -1;
	}


	return ast_bridge_impart(ast_channel_internal_bridge(p->input), p->output, NULL, NULL, 0)
		? -1 : 0;
}
