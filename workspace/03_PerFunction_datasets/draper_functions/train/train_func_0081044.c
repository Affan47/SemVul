realtime_canmatch(struct ast_channel *chan, const char *context, const char *exten, int priority, const char *callerid, const char *data)
{
	struct ast_variable *var = realtime_common(context, exten, priority, data, MODE_CANMATCH);
	if (var) {
		ast_variables_destroy(var);
		return 1;
	}
	return 0;
}
