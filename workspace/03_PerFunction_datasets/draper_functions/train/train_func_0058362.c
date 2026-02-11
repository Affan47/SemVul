language_names(void)
{
	static char names[512];
	mowgli_node_t *n;
	language_t *lang;

	names[0] = '\0';
	MOWGLI_ITER_FOREACH(n, language_list.head)
	{
		lang = n->data;
		if (lang->flags & LANG_VALID)
		{
			if (names[0] != '\0')
				strlcat(names, " ", sizeof names);
			strlcat(names, lang->name, sizeof names);
		}
	}
	return names;
}
