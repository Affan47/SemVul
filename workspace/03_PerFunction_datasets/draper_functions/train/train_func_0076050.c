ast_call(struct ast_channel *chan, const char *addr, int timeout)
{


	int res = -1;

	ast_channel_lock(chan);
	if (!ast_test_flag(ast_channel_flags(chan), AST_FLAG_ZOMBIE) && !ast_check_hangup(chan)) {
		if (ast_channel_cdr(chan)) {
			ast_set_flag(ast_channel_cdr(chan), AST_CDR_FLAG_DIALED);
		}
		if (ast_channel_tech(chan)->call)
			res = ast_channel_tech(chan)->call(chan, addr, timeout);
		ast_set_flag(ast_channel_flags(chan), AST_FLAG_OUTGOING);
	}
	ast_channel_unlock(chan);
	return res;
}
