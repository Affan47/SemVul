unload_module(void)
{
	int res = 0;
	int i = 0;

	for (i = 0; i < ARRAY_LEN(slin_list); i++) {
		if (ast_format_def_unregister(slin_list[i]->name)) {
			res |= AST_MODULE_LOAD_FAILURE;
		}
	}
	return res;
}
