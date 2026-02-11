pbx_builtin_setvar_helper(struct ast_channel *chan, const char *name, const char *value)
{
	struct ast_var_t *newvariable;
	struct varshead *headp;
	const char *nametail = name;

	if (name[strlen(name) - 1] == ')') {
		char *function = ast_strdupa(name);

		return ast_func_write(chan, function, value);
	}

	if (chan) {
		ast_channel_lock(chan);
		headp = ast_channel_varshead(chan);
	} else {
		ast_rwlock_wrlock(&globalslock);
		headp = &globals;
	}


	if (*nametail == '_') {
		nametail++;
		if (*nametail == '_')
			nametail++;
	}

	AST_LIST_TRAVERSE_SAFE_BEGIN(headp, newvariable, entries) {
		if (strcmp(ast_var_name(newvariable), nametail) == 0) {

			AST_LIST_REMOVE_CURRENT(entries);
			ast_var_delete(newvariable);
			break;
		}
	}
	AST_LIST_TRAVERSE_SAFE_END;

	if (value && (newvariable = ast_var_assign(name, value))) {
		if (headp == &globals)
			ast_verb(2, "Setting global variable '%s' to '%s'\n", name, value);
		AST_LIST_INSERT_HEAD(headp, newvariable, entries);


		manager_event(EVENT_FLAG_DIALPLAN, "VarSet",
			"Channel: %s\r\n"
			"Variable: %s\r\n"
			"Value: %s\r\n"
			"Uniqueid: %s\r\n",
			chan ? ast_channel_name(chan) : "none", name, value,
			chan ? ast_channel_uniqueid(chan) : "none");
	}

	if (chan)
		ast_channel_unlock(chan);
	else
		ast_rwlock_unlock(&globalslock);
	return 0;
}
