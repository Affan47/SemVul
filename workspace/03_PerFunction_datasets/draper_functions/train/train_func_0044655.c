ast_context_verify_includes(struct ast_context *con)
{
	struct ast_include *inc = NULL;
	int res = 0;

	while ( (inc = ast_walk_context_includes(con, inc)) ) {
		if (ast_context_find(inc->rname))
			continue;

		res = -1;
		ast_log(LOG_WARNING, "Context '%s' tries to include nonexistent context '%s'\n",
			ast_get_context_name(con), inc->rname);
		break;
	}

	return res;
}
