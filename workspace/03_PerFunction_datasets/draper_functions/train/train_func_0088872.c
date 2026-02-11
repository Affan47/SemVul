pbx_load_module(void)
{
	struct ast_context *con;

	ast_mutex_lock(&reload_lock);

	if (!local_table)
		local_table = ast_hashtab_create(17, ast_hashtab_compare_contexts, ast_hashtab_resize_java, ast_hashtab_newsize_java, ast_hashtab_hash_contexts, 0);

	if (!pbx_load_config(config)) {
		ast_mutex_unlock(&reload_lock);
		return AST_MODULE_LOAD_DECLINE;
	}

	pbx_load_users();

	ast_merge_contexts_and_delete(&local_contexts, local_table, registrar);
	local_table = NULL;
	local_contexts = NULL;

	ast_mutex_unlock(&reload_lock);

	for (con = NULL; (con = ast_walk_contexts(con));)
		ast_context_verify_includes(con);

	pbx_set_overrideswitch(overrideswitch_config);
	pbx_set_autofallthrough(autofallthrough_config);
	pbx_set_extenpatternmatchnew(extenpatternmatchnew_config);

	return AST_MODULE_LOAD_SUCCESS;
}
