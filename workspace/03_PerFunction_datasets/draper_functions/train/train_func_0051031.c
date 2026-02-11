exec_exec(struct ast_channel *chan, const char *data)
{
	int res = 0;
	char *s, *appname, *endargs;
	struct ast_app *app;
	struct ast_str *args = NULL;

	if (ast_strlen_zero(data))
		return 0;

	s = ast_strdupa(data);
	appname = strsep(&s, "(");
	if (s) {
		endargs = strrchr(s, ')');
		if (endargs)
			*endargs = '\0';
		if ((args = ast_str_create(16))) {
			ast_str_substitute_variables(&args, 0, chan, s);
		}
	}
	if (appname) {
		app = pbx_findapp(appname);
		if (app) {
			res = pbx_exec(chan, app, args ? ast_str_buffer(args) : NULL);
		} else {
			ast_log(LOG_WARNING, "Could not find application (%s)\n", appname);
			res = -1;
		}
	}

	ast_free(args);
	return res;
}
