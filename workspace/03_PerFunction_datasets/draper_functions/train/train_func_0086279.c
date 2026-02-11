module_kallsyms_on_each_symbol(int (*fn)(void *, const char *,
					     struct module *, unsigned long),
				   void *data)
{
	struct module *mod;
	unsigned int i;
	int ret;

	module_assert_mutex();

	list_for_each_entry(mod, &modules, list) {

		struct mod_kallsyms *kallsyms = mod->kallsyms;

		if (mod->state == MODULE_STATE_UNFORMED)
			continue;
		for (i = 0; i < kallsyms->num_symtab; i++) {
			ret = fn(data, symname(kallsyms, i),
				 mod, kallsyms->symtab[i].st_value);
			if (ret != 0)
				return ret;
		}
	}
	return 0;
}
