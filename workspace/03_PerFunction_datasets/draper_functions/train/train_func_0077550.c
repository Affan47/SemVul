unload_module(void)
{
	ast_cdr_unregister(name);
	if (customfields)
		ast_free(customfields);

	return 0;
}
