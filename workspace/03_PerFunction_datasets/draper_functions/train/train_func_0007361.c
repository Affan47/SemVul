s_buildHashNames (std::vector<std::string> & names, EnchantBroker * broker, const char * dict)
{
	names.clear ();

	GSList *dirs, *iter;

	dirs = ispell_checker_get_dictionary_dirs(broker);
	for (iter = dirs; iter; iter = iter->next)
		{
			char *tmp;

			tmp = g_build_filename ((const gchar *)iter->data, dict, NULL);
			names.push_back (tmp);
			g_free (tmp);
		}

	g_slist_foreach (dirs, (GFunc)g_free, NULL);
	g_slist_free (dirs);
}
