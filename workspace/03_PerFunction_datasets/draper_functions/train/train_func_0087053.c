ve_config_get_translated_string (VeConfig *config,
				 const char *key)
{
	char *dkey;
	char *def;
	VeLine *line = NULL;
	char *ret;
	const char * const* langs;
	int i;

	g_return_val_if_fail (config != NULL, NULL);
	g_return_val_if_fail (key != NULL, NULL);

	dkey = g_strdup (key);
	def = strchr (dkey, '=');
	if (def != NULL) {
		*def = '\0';
		def++;
	}

	langs = g_get_language_names ();
	for (i = 0; langs[i] != NULL; i++) {
		char *full = g_strdup_printf ("%s[%s]", dkey, langs[i]);
		line = g_hash_table_lookup (config->line_ht, full);
		g_free (full);
		if (line != NULL)
			break;
	}
	if (line == NULL)
		line = g_hash_table_lookup (config->line_ht, dkey);

	if (line != NULL)
		ret = g_strdup (line->string);
	else
		ret = g_strdup (def);
	g_free (dkey);
	return ret;
}
