acf_if(struct ast_channel *chan, const char *cmd, char *data, char *buf,
		  size_t len)
{
	AST_DECLARE_APP_ARGS(args1,
		AST_APP_ARG(expr);
		AST_APP_ARG(remainder);
	);
	AST_DECLARE_APP_ARGS(args2,
		AST_APP_ARG(iftrue);
		AST_APP_ARG(iffalse);
	);
	args2.iftrue = args2.iffalse = NULL;


	AST_NONSTANDARD_APP_ARGS(args1, data, '?');
	AST_NONSTANDARD_APP_ARGS(args2, args1.remainder, ':');

	if (ast_strlen_zero(args1.expr) || !(args2.iftrue || args2.iffalse)) {
		ast_log(LOG_WARNING, "Syntax IF(<expr>?[<true>][:<false>])  (expr must be non-null, and either <true> or <false> must be non-null)\n");
		ast_log(LOG_WARNING, "      In this case, <expr>='%s', <true>='%s', and <false>='%s'\n", args1.expr, args2.iftrue, args2.iffalse);
		return -1;
	}

	args1.expr = ast_strip(args1.expr);
	if (args2.iftrue)
		args2.iftrue = ast_strip(args2.iftrue);
	if (args2.iffalse)
		args2.iffalse = ast_strip(args2.iffalse);

	ast_copy_string(buf, pbx_checkcondition(args1.expr) ? (S_OR(args2.iftrue, "")) : (S_OR(args2.iffalse, "")), len);

	return 0;
}
