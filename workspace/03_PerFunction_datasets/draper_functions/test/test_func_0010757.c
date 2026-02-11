new_module(const char *modname)
{
	struct module *mod;
	char *p;

	mod = NOFAIL(malloc(sizeof(*mod)));
	memset(mod, 0, sizeof(*mod));
	p = NOFAIL(strdup(modname));


	if (strends(p, ".o")) {
		p[strlen(p) - 2] = '\0';
		mod->is_dot_o = 1;
	}


	mod->name = p;
	mod->gpl_compatible = -1;
	mod->next = modules;
	modules = mod;

	return mod;
}
