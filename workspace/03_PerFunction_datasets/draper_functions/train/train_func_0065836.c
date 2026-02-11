conf_set_now (char *section, char *tag, char *value, int override,
	      int is_default)
{
	struct conf_binding *node = 0;

	if (override)
		conf_remove_now (section, tag);
	else if (conf_get_str (section, tag)) {
		if (!is_default)
			warnx("conf_set: duplicate tag [%s]:%s, ignoring...\n",
			      section, tag);
		return (1);
	}

	node = calloc (1, sizeof *node);
	if (!node) {
		warn("conf_set: calloc (1, %d) failed", sizeof *node);
		return (1);
	}
	node->section = strdup (section);
	node->tag = strdup (tag);
	node->value = strdup (value);
	node->is_default = is_default;

	LIST_INSERT_HEAD (&conf_bindings[conf_hash (section)], node, link);
	return (0);
}
