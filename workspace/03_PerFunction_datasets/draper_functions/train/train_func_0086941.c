unshift_push(struct ast_channel *chan, const char *cmd, char *data, const char *new_value)
{
#define beginning	(cmd[0] == 'U')
	char delimiter[2] = ",", *varsubst;
	size_t unused;
	struct ast_str *buf, *previous_value;
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(var);
		AST_APP_ARG(delimiter);
	);

	if (!(buf = ast_str_thread_get(&result_buf, 16)) ||
		!(previous_value = ast_str_thread_get(&tmp_buf, 16))) {
		return -1;
	}

	AST_STANDARD_APP_ARGS(args, data);

	if (ast_strlen_zero(args.var)) {
		ast_log(LOG_WARNING, "%s requires a variable name\n", cmd);
		return -1;
	}

	if (args.argc > 1 && !ast_strlen_zero(args.delimiter)) {
		ast_get_encoded_char(args.delimiter, delimiter, &unused);
	}

	varsubst = ast_alloca(strlen(args.var) + 4);
	sprintf(varsubst, "${%s}", args.var);
	ast_str_substitute_variables(&previous_value, 0, chan, varsubst);

	if (!ast_str_strlen(previous_value)) {
		ast_str_set(&buf, 0, "%s", new_value);
	} else {
		ast_str_set(&buf, 0, "%s%c%s",
			beginning ? new_value : ast_str_buffer(previous_value),
			delimiter[0],
			beginning ? ast_str_buffer(previous_value) : new_value);
	}

	pbx_builtin_setvar_helper(chan, args.var, ast_str_buffer(buf));

	return 0;
#undef beginning
}
