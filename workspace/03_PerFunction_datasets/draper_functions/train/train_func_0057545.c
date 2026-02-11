find_context_locked(const char *context)
{
	struct ast_context *c;
	struct fake_context item;

	ast_copy_string(item.name, context, sizeof(item.name));

	ast_rdlock_contexts();
	c = ast_hashtab_lookup(contexts_table, &item);
	if (!c) {
		ast_unlock_contexts();
	}

	return c;
}
