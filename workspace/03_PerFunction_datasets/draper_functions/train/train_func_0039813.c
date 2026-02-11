get_environ(const gchar *p_proc_path)
{

	gchar *proc_environ = g_strdup_printf("%s/environ", p_proc_path);
#ifdef DEBUG_VERBOSE
	purple_debug_misc("gfire", "get_environ: Reading environment from \"%s\"\n", proc_environ);
#endif

	FILE *fenviron = fopen(proc_environ, "r");
	g_free(proc_environ);

	if(!fenviron)
	{
#ifdef DEBUG
		purple_debug_error("gfire", "get_environ: fopen() failed\n");
#endif
		return NULL;
	}

	GHashTable *ret = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

	gchar *line = NULL;
	size_t line_len = 0;

	while(getdelim(&line, &line_len, 0, fenviron) != -1)
	{
		const gchar *equal = strchr(line, '=');
		if(!equal)
			continue;

		g_hash_table_insert(ret, g_strndup(line, equal - line), g_strdup(equal + 1));
	}
	fclose(fenviron);
	g_free(line);

#ifdef DEBUG_VERBOSE
	purple_debug_misc("gfire", "get_environ: saved %u values\n", g_hash_table_size(ret));
#endif
	return ret;
}
