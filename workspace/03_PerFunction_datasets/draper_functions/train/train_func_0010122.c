g_vfs_backend_add_auto_info (GVfsBackend *backend,
			     GFileAttributeMatcher *matcher,
			     GFileInfo *info,
			     const char *uri)
{
  GMountSpec *spec;
  char *id;

  if (g_file_attribute_matcher_matches (matcher,
					G_FILE_ATTRIBUTE_ID_FILESYSTEM))
    {
      spec = g_vfs_backend_get_mount_spec (backend);
      if (spec)
	{
	  id = g_mount_spec_to_string (spec);
	  g_file_info_set_attribute_string (info,
					    G_FILE_ATTRIBUTE_ID_FILESYSTEM,
					    id);
	  g_free (id);
	}
    }

  if (uri != NULL &&
      g_file_attribute_matcher_matches (matcher,
					G_FILE_ATTRIBUTE_THUMBNAIL_PATH))
    get_thumbnail_attributes (uri, info);

}
