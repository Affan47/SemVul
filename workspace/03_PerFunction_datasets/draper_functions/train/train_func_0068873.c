check_parents (GSList *schemes, GHashTable *hash)
{
	GSList *to_check;

	to_check = g_slist_copy (schemes);

	while (to_check != NULL)
	{
		GtkSourceStyleScheme *scheme_to_check;
		GSList *chain;
		gboolean valid;

		scheme_to_check = to_check->data;

		valid = build_reference_chain (scheme_to_check, hash, &chain);

		while (chain != NULL)
		{
			GtkSourceStyleScheme *scheme = chain->data;

			to_check = g_slist_remove (to_check, scheme);

			if (!valid)
			{
				const gchar *id = gtk_source_style_scheme_get_id (scheme);
				schemes = g_slist_remove (schemes, scheme);
				g_hash_table_remove (hash, id);
			}

			chain = g_slist_delete_link (chain, chain);
		}
	}

	return schemes;
}
