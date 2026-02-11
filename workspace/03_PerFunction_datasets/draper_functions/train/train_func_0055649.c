load_module(void)
{
	if (!(cli_aliases = ao2_container_alloc(MAX_ALIAS_BUCKETS, alias_hash_cb, alias_cmp_cb))) {
		return AST_MODULE_LOAD_DECLINE;
	}

	load_config(0);

	ast_cli_register_multiple(cli_alias, ARRAY_LEN(cli_alias));

	return AST_MODULE_LOAD_SUCCESS;
}
