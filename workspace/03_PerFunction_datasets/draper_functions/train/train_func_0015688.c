presence_write(struct ast_channel *chan, const char *cmd, char *data, const char *value)
{
	size_t len = strlen("CustomPresence:");
	char *tmp = data;
	char *args = ast_strdupa(value);
	enum ast_presence_state state;
	char *options, *message, *subtype;

	if (strncasecmp(data, "CustomPresence:", len)) {
		ast_log(LOG_WARNING, "The PRESENCE_STATE function can only set CustomPresence: presence providers.\n");
		return -1;
	}
	data += len;
	if (ast_strlen_zero(data)) {
		ast_log(LOG_WARNING, "PRESENCE_STATE function called with no custom device name!\n");
		return -1;
	}

	if (parse_data(args, &state, &subtype, &message, &options)) {
		ast_log(LOG_WARNING, "Invalid arguments to PRESENCE_STATE\n");
		return -1;
	}

	ast_db_put(astdb_family, data, value);

	ast_presence_state_changed_literal(state, subtype, message, tmp);

	return 0;
}
