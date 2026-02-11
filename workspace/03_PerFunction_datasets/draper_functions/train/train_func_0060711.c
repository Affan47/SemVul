gel_get_help (const char *func, gboolean insert)
{
	GelHelp *help;

	if (get_help_cache != NULL &&


	    get_help_func_cache == func &&
	    strcmp (get_help_cache->func, func) == 0)
		return get_help_cache;

	if G_UNLIKELY (gel_helphash == NULL)
		gel_helphash = g_hash_table_new (g_str_hash, g_str_equal);

	help = g_hash_table_lookup (gel_helphash, func);

	if (help == NULL && insert) {
		help = g_new0 (GelHelp, 1);
		help->func = g_strdup (func);
		g_hash_table_insert (gel_helphash, help->func, help);
	}

	if (help != NULL) {
		get_help_func_cache = func;
		get_help_cache = help;
	}

	return help;
}
