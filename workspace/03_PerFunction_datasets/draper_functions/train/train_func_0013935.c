find_section (VeConfig *config, const char *name)
{
	GList *li;

	if (name == NULL) {
		return config->root;
	}

	for (li = config->sections; li != NULL; li = li->next) {
		VeSection *section = li->data;
		if (strcmp (section->name, name) == 0)
			return section;
	}
	return NULL;
}
