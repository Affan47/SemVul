handle_cli_config_reload(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{
	struct cache_file_mtime *cfmtime;
	char *prev = "", *completion_value = NULL;
	int wordlen, which = 0;

	switch (cmd) {
	case CLI_INIT:
		e->command = "config reload";
		e->usage =
			"Usage: config reload <filename.conf>\n"
			"   Reloads all modules that reference <filename.conf>\n";
		return NULL;
	case CLI_GENERATE:
		if (a->pos > 2) {
			return NULL;
		}

		wordlen = strlen(a->word);

		AST_LIST_LOCK(&cfmtime_head);
		AST_LIST_TRAVERSE(&cfmtime_head, cfmtime, list) {

			if (strcmp(cfmtime->filename, prev) == 0) {
				continue;
			}


			if (ast_strlen_zero(cfmtime->who_asked)) {
				continue;
			}

			if (++which > a->n && strncmp(cfmtime->filename, a->word, wordlen) == 0) {
				completion_value = ast_strdup(cfmtime->filename);
				break;
			}


			prev = cfmtime->filename;
		}
		AST_LIST_UNLOCK(&cfmtime_head);

		return completion_value;
	}

	if (a->argc != 3) {
		return CLI_SHOWUSAGE;
	}

	AST_LIST_LOCK(&cfmtime_head);
	AST_LIST_TRAVERSE(&cfmtime_head, cfmtime, list) {
		if (!strcmp(cfmtime->filename, a->argv[2])) {
			char *buf = ast_alloca(strlen("module reload ") + strlen(cfmtime->who_asked) + 1);
			sprintf(buf, "module reload %s", cfmtime->who_asked);
			ast_cli_command(a->fd, buf);
		}
	}
	AST_LIST_UNLOCK(&cfmtime_head);

	return CLI_SUCCESS;
}
