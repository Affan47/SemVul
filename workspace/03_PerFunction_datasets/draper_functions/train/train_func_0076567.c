func_inheritance_write(struct ast_channel *chan, const char *function, char *data, const char *value)
{
	int allow;
	struct ast_datastore *datastore = NULL;
	struct audiohook_inheritance_datastore *inheritance_datastore = NULL;
	struct inheritable_audiohook *inheritable_audiohook;


	if (ast_strlen_zero(data)) {
		ast_log(LOG_WARNING, "No argument provided to INHERITANCE function.\n");
		return -1;
	}

	if (ast_strlen_zero(value)) {
		ast_log(LOG_WARNING, "No value provided to INHERITANCE function.\n");
		return -1;
	}

	allow = ast_true(value);


	ast_channel_lock(chan);
	if (!(datastore = ast_channel_datastore_find(chan, &audiohook_inheritance_info, NULL))) {
		ast_channel_unlock(chan);

		if (!allow) {
			ast_debug(1, "Audiohook %s is already set to not be inheritable on channel %s\n", data, ast_channel_name(chan));
			return 0;
		} else if (!(inheritance_datastore = setup_inheritance_datastore(chan))) {
			ast_log(LOG_WARNING, "Unable to set up audiohook inheritance datastore on channel %s\n", ast_channel_name(chan));
			return -1;
		} else {
			return setup_inheritable_audiohook(inheritance_datastore, data);
		}
	} else {
		inheritance_datastore = datastore->data;
	}
	ast_channel_unlock(chan);


	AST_LIST_TRAVERSE_SAFE_BEGIN(&inheritance_datastore->allowed_list, inheritable_audiohook, list) {
		if (!strcasecmp(inheritable_audiohook->source, data)) {
			if (allow) {
				ast_debug(2, "Audiohook source %s is already set up to be inherited from channel %s\n", data, ast_channel_name(chan));
				return 0;
			} else {
				ast_debug(2, "Removing inheritability of audiohook %s from channel %s\n", data, ast_channel_name(chan));
				AST_LIST_REMOVE_CURRENT(list);
				ast_free(inheritable_audiohook);
				return 0;
			}
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;


	if (allow) {
		return setup_inheritable_audiohook(inheritance_datastore, data);
	} else {
		ast_debug(1, "Audiohook %s is already set to not be inheritable on channel %s\n", data, ast_channel_name(chan));
		return 0;
	}
}
