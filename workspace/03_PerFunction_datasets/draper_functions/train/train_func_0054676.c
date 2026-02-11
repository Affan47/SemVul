g_i18n_get_language_list (const gchar *category_name)
{
  GList *list;
  prepped_table = 0;

	if (!category_name)
		category_name= "LC_ALL";

	if (category_table)
    {
#if 0


		list= static_cast<GList *>(g_hash_table_lookup (category_table, const_cast<const gpointer>(category_name)));
#else
		xxx_UT_DEBUGMSG(("recreating hash table\n"));
		g_hash_table_destroy (category_table);
        category_table= g_hash_table_new (g_str_hash, g_str_equal);
        list= NULL;

#endif
    }
	else
    {
		category_table= g_hash_table_new (g_str_hash, g_str_equal);
		list= NULL;
    }

	if (!list)
    {
		gint c_locale_defined= FALSE;

		const gchar *category_value;
		gchar *category_memory, *orig_category_memory;

		category_value = guess_category_value (category_name);
		if (! category_value)
			category_value = "C";
		orig_category_memory = category_memory =
			static_cast<gchar*>(g_malloc (strlen (category_value)+1));

		while (category_value[0] != '\0')
		{
			while (category_value[0] != '\0' && category_value[0] == ':')
				++category_value;

			if (category_value[0] != '\0')
			{
				char *cp= category_memory;

				while (category_value[0] != '\0' && category_value[0] != ':')
					*category_memory++= *category_value++;

				category_memory[0]= '\0';
				category_memory++;

				cp = unalias_lang(cp);

				if (strcmp (cp, "C") == 0)
					c_locale_defined= TRUE;

				list= g_list_concat (list, compute_locale_variants (cp));
			}
		}

		g_free (orig_category_memory);

		if (!c_locale_defined)
			list= g_list_append (list, reinterpret_cast<void*>(const_cast<gchar *>("C")));

		g_hash_table_insert (category_table, reinterpret_cast<gpointer>(const_cast<gchar *>(category_name)), list);
    }

   g_hash_table_foreach(alias_table, free_entry, NULL);
   g_hash_table_destroy(alias_table);
   prepped_table = 0;

  return list;
}
