get_keycode(const struct query_mode *query_mode, const char *kstr)
{
	if (isdigit(kstr[0])) {
		unsigned long val;
		errno = 0;
		val = strtoul(kstr, NULL, 0);
		if (errno) {
			fprintf(stderr, "Could not interpret value %s\n", kstr);
			return -1;
		}
		return (int) val;
	} else {
		const char * const *keynames = names[query_mode->event_type];
		int i;

		for (i = 0; i < query_mode->max; i++) {
			const char *name = keynames[i];
			if (name && strcmp(name, kstr) == 0)
				return i;
		}

		return -1;
	}
}
