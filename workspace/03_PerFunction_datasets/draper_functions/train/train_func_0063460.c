refresh_tile_time (ChamplainTileCache *tile_cache,
    ChamplainTile *tile)
{
  g_return_if_fail (CHAMPLAIN_IS_FILE_CACHE (tile_cache));

  ChamplainMapSource *map_source = CHAMPLAIN_MAP_SOURCE (tile_cache);
  ChamplainMapSource *next_source = champlain_map_source_get_next_source (map_source);
  ChamplainFileCache *file_cache = CHAMPLAIN_FILE_CACHE (tile_cache);
  gchar *filename = NULL;
  GFile *file;
  GFileInfo *info;

  filename = get_filename (file_cache, tile);
  file = g_file_new_for_path (filename);
  g_free (filename);

  info = g_file_query_info (file, G_FILE_ATTRIBUTE_TIME_MODIFIED,
        G_FILE_QUERY_INFO_NONE, NULL, NULL);

  if (info)
    {
      GTimeVal now = { 0, };

      g_get_current_time (&now);

      g_file_info_set_modification_time (info, &now);
      g_file_set_attributes_from_info (file, info, G_FILE_QUERY_INFO_NONE, NULL, NULL);

      g_object_unref (info);
    }

  g_object_unref (file);

  if (CHAMPLAIN_IS_TILE_CACHE (next_source))
    champlain_tile_cache_refresh_tile_time (CHAMPLAIN_TILE_CACHE (next_source), tile);
}
