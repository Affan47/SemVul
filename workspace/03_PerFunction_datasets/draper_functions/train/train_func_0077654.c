__ast_goto_if_exists(struct ast_channel *chan, const char *context, const char *exten, int priority, int async)
{
	int (*goto_func)(struct ast_channel *chan, const char *context, const char *exten, int priority);

	if (!chan)
		return -2;

	if (context == NULL)
		context = ast_channel_context(chan);
	if (exten == NULL)
		exten = ast_channel_exten(chan);

	goto_func = (async) ? ast_async_goto : ast_explicit_goto;
	if (ast_exists_extension(chan, context, exten, priority,
		S_COR(ast_channel_caller(chan)->id.number.valid, ast_channel_caller(chan)->id.number.str, NULL)))
		return goto_func(chan, context, exten, priority);
	else {
		return AST_PBX_GOTO_FAILED;
	}
}
