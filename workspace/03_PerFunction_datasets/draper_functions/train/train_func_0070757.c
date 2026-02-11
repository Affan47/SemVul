unload_dynamic_module(struct ast_module *mod)
{
	void *lib = mod->lib;


	if (lib)
		while (!dlclose(lib));
}
