cache_reaper_source_added_cb (ESourceRegistryServer *server,
                              ESource *source,
                              ECacheReaper *extension)
{
	guint ii;


	for (ii = 0; ii < extension->n_data_directories; ii++)
		cache_reaper_recover_from_trash (
			extension, source,
			extension->data_directories[ii],
			extension->data_trash_directories[ii]);

	for (ii = 0; ii < extension->n_cache_directories; ii++)
		cache_reaper_recover_from_trash (
			extension, source,
			extension->cache_directories[ii],
			extension->cache_trash_directories[ii]);
}
