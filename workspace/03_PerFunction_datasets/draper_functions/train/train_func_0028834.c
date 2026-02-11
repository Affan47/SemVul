find_module(snd_mixer_class_t *class, snd_config_t *top)
{
	snd_config_iterator_t i, next;
	snd_config_iterator_t j, jnext;
	char *lib, *searchl;
	const char *id;
	int err;

	snd_config_for_each(i, next, top) {
		snd_config_t *n = snd_config_iterator_entry(i);
		if (snd_config_get_id(n, &id) < 0)
			continue;
		if (*id == '_')
			continue;
		searchl = NULL;
		lib = NULL;
		snd_config_for_each(j, jnext, n) {
			snd_config_t *m = snd_config_iterator_entry(j);
			if (snd_config_get_id(m, &id) < 0)
				continue;
			if (!strcmp(id, "searchl")) {
				err = snd_config_get_string(m, (const char **)&searchl);
				if (err < 0)
					return err;
				continue;
			}
			if (!strcmp(id, "lib")) {
				err = snd_config_get_string(m, (const char **)&lib);
				if (err < 0)
					return err;
				continue;
			}
		}
		err = match(class, lib, searchl);
		if (err == 1)
			return 0;
		if (err < 0)
			return err;
	}
	return -ENOENT;
}
