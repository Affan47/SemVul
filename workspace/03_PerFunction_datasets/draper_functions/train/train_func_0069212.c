ast_channel_by_exten_cb(void *obj, void *arg, void *data, int flags)
{
	struct ast_channel *chan = obj;
	char *context = arg;
	char *exten = data;
	int ret = CMP_MATCH;

	if (ast_strlen_zero(exten) || ast_strlen_zero(context)) {
		ast_log(LOG_ERROR, "BUG! Must have a context and extension to match!\n");
		return CMP_STOP;
	}

	ast_channel_lock(chan);
	if (strcasecmp(ast_channel_context(chan), context) && strcasecmp(ast_channel_macrocontext(chan), context)) {
		ret = 0;
	} else if (strcasecmp(ast_channel_exten(chan), exten) && strcasecmp(ast_channel_macroexten(chan), exten)) {
		ret = 0;
	}
	ast_channel_unlock(chan);

	return ret;
}
