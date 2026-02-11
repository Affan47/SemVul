add_key_line (VeConfig *config, VeSection *section,
	      const char *key, const char *val,
	      gboolean careful_add)
{
	VeLine *line = g_new0 (VeLine, 1);
	line->type = VE_LINE_KEY;
	line->parent = section;
	if (section->name == NULL) {
		line->fullkey = g_strdup (key);
		line->key = line->fullkey;
	} else {
		line->fullkey = g_strdup_printf ("%s/%s",
						 section->name,
						 key);
		line->key = strchr (line->fullkey, '/');
		line->key ++;
	}
	line->string = g_strdup (val);


	if (g_hash_table_lookup (config->line_ht, line->fullkey) != NULL) {
		free_line (line);
		return;
	}

	if ( ! careful_add ||
	    section->lines == NULL) {
		section->lines = g_list_append (section->lines, line);
	} else {
		careful_append (section, line);
	}

	g_hash_table_insert (config->line_ht,
			     line->fullkey,
			     line);
}
