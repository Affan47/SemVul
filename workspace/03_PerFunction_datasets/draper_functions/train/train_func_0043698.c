output_devname(struct depmod *depmod, FILE *out)
{
	size_t i;

	fputs("# Device nodes to trigger on-demand module loading.\n", out);

	for (i = 0; i < depmod->modules.count; i++) {
		const struct mod *mod = depmod->modules.array[i];
		struct kmod_list *l, *list = NULL;
		const char *devname = NULL;
		char type = '\0';
		unsigned int major = 0, minor = 0;
		int r;

		r = kmod_module_get_info(mod->kmod, &list);
		if (r < 0 || list == NULL)
			continue;

		kmod_list_foreach(l, list) {
			const char *key = kmod_module_info_get_key(l);
			const char *value = kmod_module_info_get_value(l);
			unsigned int maj, min;

			if (!streq(key, "alias"))
				continue;

			if (strstartswith(value, "devname:"))
				devname = value + sizeof("devname:") - 1;
			else if (sscanf(value, "char-major-%u-%u",
						&maj, &min) == 2) {
				type = 'c';
				major = maj;
				minor = min;
			} else if (sscanf(value, "block-major-%u-%u",
						&maj, &min) == 2) {
				type = 'b';
				major = maj;
				minor = min;
			}

			if (type != '\0' && devname != NULL) {
				fprintf(out, "%s %s %c%u:%u\n",
					kmod_module_get_name(mod->kmod),
					devname, type, major, minor);
				break;
			}
		}
		kmod_module_info_free_list(list);
	}

	return 0;
}
