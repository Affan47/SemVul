e_categories_remove (const gchar *category)
{
	gchar *collation_key;

	g_return_if_fail (category != NULL);

	if (!initialized)
		initialize_categories ();

	collation_key = get_collation_key (category);

	if (g_hash_table_remove (categories_table, collation_key)) {
		changed = TRUE;
		save_categories ();
	}

	g_free (collation_key);
}
