handle_cli_database_query(struct ast_cli_entry *e, int cmd, struct ast_cli_args *a)
{

	switch (cmd) {
	case CLI_INIT:
		e->command = "database query";
		e->usage =
			"Usage: database query \"<SQL Statement>\"\n"
			"       Run a user-specified SQL query on the database. Be careful.\n";
		return NULL;
	case CLI_GENERATE:
		return NULL;
	}

	if (a->argc != 3) {
		return CLI_SHOWUSAGE;
	}

	ast_mutex_lock(&dblock);
	db_execute_sql(a->argv[2], display_results, a);
	db_sync();
	ast_mutex_unlock(&dblock);

	return CLI_SUCCESS;
}
