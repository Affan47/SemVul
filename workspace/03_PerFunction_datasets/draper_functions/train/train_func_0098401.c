load_module(void)
{
	if (!(class_container = ao2_container_alloc(1, null_hash_fn, ao2_match_by_addr)))
		return AST_MODULE_LOAD_DECLINE;
	if (load_odbc_config() == -1)
		return AST_MODULE_LOAD_DECLINE;
	ast_cli_register_multiple(cli_odbc, ARRAY_LEN(cli_odbc));
	ast_data_register_multiple(odbc_providers, ARRAY_LEN(odbc_providers));
	ast_register_application_xml(app_commit, commit_exec);
	ast_register_application_xml(app_rollback, rollback_exec);
	ast_custom_function_register(&odbc_function);
	ast_log(LOG_NOTICE, "res_odbc loaded.\n");
	return 0;
}
