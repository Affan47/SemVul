iftime(struct ast_channel *chan, const char *cmd, char *data, char *buf,
		  size_t len)
{
	struct ast_timing timing;
	char *expr;
	char *iftrue;
	char *iffalse;

	data = ast_strip_quoted(data, "\"", "\"");
	expr = strsep(&data, "?");
	iftrue = strsep(&data, ":");
	iffalse = data;

	if (ast_strlen_zero(expr) || !(iftrue || iffalse)) {
		ast_log(LOG_WARNING,
				"Syntax IFTIME(<timespec>?[<true>][:<false>])\n");
		return -1;
	}

	if (!ast_build_timing(&timing, expr)) {
		ast_log(LOG_WARNING, "Invalid Time Spec.\n");
		ast_destroy_timing(&timing);
		return -1;
	}

	if (iftrue)
		iftrue = ast_strip_quoted(iftrue, "\"", "\"");
	if (iffalse)
		iffalse = ast_strip_quoted(iffalse, "\"", "\"");

	ast_copy_string(buf, ast_check_timing(&timing) ? S_OR(iftrue, "") : S_OR(iffalse, ""), len);
	ast_destroy_timing(&timing);

	return 0;
}
