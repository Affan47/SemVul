pbx_builtin_answer(struct ast_channel *chan, const char *data)
{
	int delay = 0;
	int answer_cdr = 1;
	char *parse;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(delay);
		AST_APP_ARG(answer_cdr);
	);

	if (ast_strlen_zero(data)) {
		return __ast_answer(chan, 0, 1);
	}

	parse = ast_strdupa(data);

	AST_STANDARD_APP_ARGS(args, parse);

	if (!ast_strlen_zero(args.delay) && (ast_channel_state(chan) != AST_STATE_UP))
		delay = atoi(data);

	if (delay < 0) {
		delay = 0;
	}

	if (!ast_strlen_zero(args.answer_cdr) && !strcasecmp(args.answer_cdr, "nocdr")) {
		answer_cdr = 0;
	}

	return __ast_answer(chan, delay, answer_cdr);
}
