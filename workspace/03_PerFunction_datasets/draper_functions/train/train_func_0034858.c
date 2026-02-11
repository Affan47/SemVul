output_aliases_bin(struct depmod *depmod, FILE *out)
{
	char buf[1024];
	struct index_node *idx;
	size_t i;

	if (out == stdout)
		return 0;

	idx = index_create();
	if (idx == NULL)
		return -ENOMEM;

	for (i = 0; i < depmod->modules.count; i++) {
		const struct mod *mod = depmod->modules.array[i];
		struct kmod_list *l, *list = NULL;
		int r = kmod_module_get_info(mod->kmod, &list);
		if (r < 0 || list == NULL)
			continue;
		kmod_list_foreach(l, list) {
			const char *key = kmod_module_info_get_key(l);
			const char *value = kmod_module_info_get_value(l);
			const char *modname, *alias;
			int duplicate;

			if (!streq(key, "alias"))
				continue;

			alias = underscores2(value, buf, sizeof(buf));
			if (alias == NULL)
				continue;

			modname = kmod_module_get_name(mod->kmod);
			duplicate = index_insert(idx, alias, modname,
						 mod->idx);
			if (duplicate && depmod->cfg->warn_dups)
				WRN("duplicate module alias:\n%s %s\n",
				    alias, modname);
		}
		kmod_module_info_free_list(list);
	}

	index_write(idx, out);
	index_destroy(idx);

	return 0;
}
