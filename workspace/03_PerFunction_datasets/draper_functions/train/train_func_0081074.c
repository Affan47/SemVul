manager_mixmonitor(struct mansession *s, const struct message *m)
{
	struct ast_channel *c = NULL;

	const char *name = astman_get_header(m, "Channel");
	const char *id = astman_get_header(m, "ActionID");
	const char *file = astman_get_header(m, "File");
	const char *options = astman_get_header(m, "Options");
	char *opts[OPT_ARG_ARRAY_SIZE] = { NULL, };
	struct ast_flags flags = { 0 };
	char *uid_channel_var = NULL;
	const char *mixmonitor_id = NULL;

	int res;
	char args[PATH_MAX] = "";
	if (ast_strlen_zero(name)) {
		astman_send_error(s, m, "No channel specified");
		return AMI_SUCCESS;
	}

	c = ast_channel_get_by_name(name);

	if (!c) {
		astman_send_error(s, m, "No such channel");
		return AMI_SUCCESS;
	}

	if (!ast_strlen_zero(options)) {
		ast_app_parse_options(mixmonitor_opts, &flags, opts, ast_strdupa(options));
	}

	snprintf(args, sizeof(args), "%s,%s", file, options);

	ast_channel_lock(c);
	res = mixmonitor_exec(c, args);

	if (ast_test_flag(&flags, MUXFLAG_UID)) {
		uid_channel_var = opts[OPT_ARG_UID];
		mixmonitor_id = pbx_builtin_getvar_helper(c, uid_channel_var);
	}
	ast_channel_unlock(c);

	if (res) {
		c = ast_channel_unref(c);
		astman_send_error(s, m, "Could not start monitoring channel");
		return AMI_SUCCESS;
	}

	astman_append(s, "Response: Success\r\n");

	if (!ast_strlen_zero(id)) {
		astman_append(s, "ActionID: %s\r\n", id);
	}

	if (!ast_strlen_zero(mixmonitor_id)) {
		astman_append(s, "MixMonitorID: %s\r\n", mixmonitor_id);
	}

	astman_append(s, "\r\n");

	c = ast_channel_unref(c);

	return AMI_SUCCESS;
}
