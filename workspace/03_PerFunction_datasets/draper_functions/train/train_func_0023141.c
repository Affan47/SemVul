dundi_precache_full(void)
{
	struct dundi_mapping *cur;
	struct ast_context *con;
	struct ast_exten *e;

	AST_LIST_TRAVERSE(&mappings, cur, list) {
		ast_log(LOG_NOTICE, "Should precache context '%s'\n", cur->dcontext);
		ast_rdlock_contexts();
		con = NULL;
		while ((con = ast_walk_contexts(con))) {
			if (strcasecmp(cur->lcontext, ast_get_context_name(con)))
				continue;

			ast_rdlock_context(con);
			e = NULL;
			while ((e = ast_walk_context_extensions(con, e)))
				reschedule_precache(ast_get_extension_name(e), cur->dcontext, 0);
			ast_unlock_context(con);
		}
		ast_unlock_contexts();
	}
}
