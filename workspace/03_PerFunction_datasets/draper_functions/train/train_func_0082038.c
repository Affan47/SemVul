load_module(void)
{
	ast_cli_register_multiple(cdr_pgsql_status_cli, sizeof(cdr_pgsql_status_cli) / sizeof(struct ast_cli_entry));
	if (config_module(0)) {
		return AST_MODULE_LOAD_DECLINE;
	}
	return ast_cdr_register(name, ast_module_info->description, pgsql_log)
		? AST_MODULE_LOAD_DECLINE : 0;
}
