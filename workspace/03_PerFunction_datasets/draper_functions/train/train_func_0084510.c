aelsub_exec(struct ast_channel *chan, const char *vdata)
{
	char buf[256], *data = ast_strdupa(vdata);
	struct ast_app *gosub = pbx_findapp("Gosub");
	AST_DECLARE_APP_ARGS(args,
		AST_APP_ARG(name);
		AST_APP_ARG(args);
	);

	if (gosub) {
		AST_STANDARD_RAW_ARGS(args, data);
		snprintf(buf, sizeof(buf), "%s,~~s~~,1(%s)", args.name, args.args);
		return pbx_exec(chan, gosub, buf);
	}
	return -1;
}
