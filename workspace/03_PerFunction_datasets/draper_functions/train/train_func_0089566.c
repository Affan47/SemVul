get_language_id (const gchar *language_name, GHashTable *mapping)
{
	gchar *name;
	gchar *language_id = NULL;

	name = g_ascii_strdown (language_name, -1);

	if (mapping != NULL)
	{
		language_id = g_hash_table_lookup (mapping, name);

		if (language_id != NULL)
		{
			g_free (name);
			return g_strdup (language_id);
		}
	}


	return name;
}
