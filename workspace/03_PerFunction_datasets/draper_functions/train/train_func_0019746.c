ipp_cache_alloc(
	const char *name, const char *item_name, const char *file_name,
	const char *description,
	const uint32 *max_cache_time, const uint32 *max_cache_size,
	const uint32 *debug)
{
	ipp_cache_t *ic;

	WALLOC(ic);
	ic->name = name;
	ic->item_name = item_name;
	ic->description = description;
	ic->max_cache_time = max_cache_time;
	ic->max_cache_size = max_cache_size;
	ic->hosts = hash_list_new(ipp_cache_item_hash, ipp_cache_item_eq);
	ic->debug = debug;
	ic->last_stored = 0;

	file_path_set(&ic->fp, g_strdup(settings_config_dir()), file_name);

	return ic;
}
