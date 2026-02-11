shift_pop(struct ast_channel *chan, const char *cmd, char *data, struct ast_str **buf, ssize_t len)
{
#define beginning	(cmd[0] == 'S')
	char *after, delimiter[2] = ",", *varsubst;
	size_t unused;
	struct ast_str *before = ast_str_thread_get(&result_buf, 16);
	char *(*search_func)(const char *s, int c) = (beginning ? strchr : strrchr);
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(var);
		AST_APP_ARG(delimiter);
	);

	if (!before) {
		return -1;
	}

	AST_STANDARD_APP_ARGS(args, data);

	if (ast_strlen_zero(args.var)) {
		ast_log(LOG_WARNING, "%s requires a variable name\n", cmd);
		return -1;
	}

	varsubst = ast_alloca(strlen(args.var) + 4);
	sprintf(varsubst, "${%s}", args.var);
	ast_str_substitute_variables(&before, 0, chan, varsubst);

	if (args.argc > 1 && !ast_strlen_zero(args.delimiter)) {
		ast_get_encoded_char(args.delimiter, delimiter, &unused);
	}

	if (!ast_str_strlen(before)) {

		return -1;
	}

	if (!(after = search_func(ast_str_buffer(before), delimiter[0]))) {

		ast_str_set(buf, len, "%s", ast_str_buffer(before));
		pbx_builtin_setvar_helper(chan, args.var, "");
	} else {
		*after++ = '\0';
		ast_str_set(buf, len, "%s", beginning ? ast_str_buffer(before) : after);
		pbx_builtin_setvar_helper(chan, args.var, beginning ? after : ast_str_buffer(before));
	}

	return 0;
#undef beginning
}
