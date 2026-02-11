kmod_module_get_options(const struct kmod_module *mod)
{
	if (mod == NULL)
		return NULL;

	if (!mod->init.options) {

		struct kmod_module *m = (struct kmod_module *)mod;
		const struct kmod_list *l;
		const struct kmod_config *config;
		char *opts = NULL;
		size_t optslen = 0;

		config = kmod_get_config(mod->ctx);

		kmod_list_foreach(l, config->options) {
			const char *modname = kmod_option_get_modname(l);
			const char *str;
			size_t len;
			void *tmp;

			DBG(mod->ctx, "modname=%s mod->name=%s mod->alias=%s\n", modname, mod->name, mod->alias);
			if (!(streq(modname, mod->name) || (mod->alias != NULL &&
						streq(modname, mod->alias))))
				continue;

			DBG(mod->ctx, "passed = modname=%s mod->name=%s mod->alias=%s\n", modname, mod->name, mod->alias);
			str = kmod_option_get_options(l);
			len = strlen(str);
			if (len < 1)
				continue;

			tmp = realloc(opts, optslen + len + 2);
			if (tmp == NULL) {
				free(opts);
				goto failed;
			}

			opts = tmp;

			if (optslen > 0) {
				opts[optslen] = ' ';
				optslen++;
			}

			memcpy(opts + optslen, str, len);
			optslen += len;
			opts[optslen] = '\0';
		}

		m->init.options = true;
		m->options = opts;
	}

	return mod->options;

failed:
	ERR(mod->ctx, "out of memory\n");
	return NULL;
}
