soup_cache_dump (SoupCache *cache)
{
	SoupCachePrivate *priv = SOUP_CACHE_GET_PRIVATE (cache);
	char *filename;
	GVariantBuilder entries_builder;
	GVariant *cache_variant;

	if (!g_list_length (cache->priv->lru_start))
		return;


	g_variant_builder_init (&entries_builder, G_VARIANT_TYPE (SOUP_CACHE_ENTRIES_FORMAT));
	g_variant_builder_add (&entries_builder, "q", SOUP_CACHE_CURRENT_VERSION);
	g_variant_builder_open (&entries_builder, G_VARIANT_TYPE ("a" SOUP_CACHE_PHEADERS_FORMAT));
	g_list_foreach (cache->priv->lru_start, pack_entry, &entries_builder);
	g_variant_builder_close (&entries_builder);


	cache_variant = g_variant_builder_end (&entries_builder);
	g_variant_ref_sink (cache_variant);
	filename = g_build_filename (priv->cache_dir, SOUP_CACHE_FILE, NULL);
	g_file_set_contents (filename, (const char *) g_variant_get_data (cache_variant),
			     g_variant_get_size (cache_variant), NULL);
	g_free (filename);
	g_variant_unref (cache_variant);
}
