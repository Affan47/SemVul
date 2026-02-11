e2_cache_time_register (gchar *name, time_t *value, time_t def)
{
	E2_Cache *cache;
	GList *found = g_list_find_custom (cache_list, name,
		(GCompareFunc) _e2_cache_str_compare);
	if (found != NULL)
	{
		printd (DEBUG, "re-register long int cache '%s'", name);
		return;
	}

	cache = ALLOCATE (E2_Cache);
	CHECKALLOCATEDFATAL (cache)
	cache->type = E2_CACHE_TYPE_TIME;
	found = g_list_find_custom (unknown_list, name,
		(GCompareFunc) _e2_cache_str_compare);
	if (found == NULL)
	{
		printd (DEBUG, "time cache '%s' not found, creating default with %d", name, def);
		cache->name = g_strdup (name);
		*value = def;
	}
	else
	{
		printd (DEBUG, "cache '%s' found", name);
		E2_Cache *unknown = found->data;
		cache->name = unknown->name;
		gchar *end = NULL;
		gchar *str = (gchar *) unknown->data;
		*value = g_ascii_strtoull (str, &end, 10);
		if (end == str)
		{
			printd (WARN, "time cache '%s' data conversion failed from '%s", name, str);
			*value = def;
		} else
			g_free (str);
		unknown_list = g_list_remove_link (unknown_list, found);
		g_list_free (found);
		g_free (unknown);
	}
	cache->data = (gpointer) value;
	cache_list = g_list_append (cache_list, cache);
	return;
}
