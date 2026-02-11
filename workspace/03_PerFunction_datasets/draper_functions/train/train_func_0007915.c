search_string_table (Workbook *wb, char const *file_name, GHashTable *targets)
{
	StringTableSearch	 state;
	GHashTable *modules;

	state.wb	= wb;
	state.targets	= targets;
	state.results	= NULL;
	go_string_foreach_base (&cb_check_strings, &state);
	g_hash_table_foreach (targets, &cb_check_func, &state);

	if (NULL != (modules = g_object_get_data (G_OBJECT (wb), "VBA")))
		g_hash_table_foreach (modules, &cb_check_module, &state);
	if (NULL != state.results) {
		g_print ("%s\n", file_name);
		g_hash_table_foreach (state.results, (GHFunc)&cb_dump_results, NULL);
		g_hash_table_destroy (state.results);
	}
}
