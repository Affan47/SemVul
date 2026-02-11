cfg_free(ConfigFile * cfg)
{
	ConfigSection *section;
	ConfigLine *line;
	GList *section_list, *line_list;

	section_list = cfg->sections;
	while (section_list)
	{
		section = (ConfigSection *) section_list->data;
		g_free(section->name);

		line_list = section->lines;
		while (line_list)
		{
			line = (ConfigLine *) line_list->data;
			g_free(line->key);
			g_free(line->value);
			g_free(line);
			line_list = g_list_next(line_list);
		}
		g_list_free(section->lines);
		g_free(section);

		section_list = g_list_next(section_list);
	}
	g_list_free(cfg->sections);
}
