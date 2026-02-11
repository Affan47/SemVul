glade_catalog_remove_path (const gchar *path)
{
  GList *l;

  if (path == NULL)
	{
	  g_list_free_full (catalog_paths, g_free);
	  catalog_paths = NULL;
	}
  else if ((l = g_list_find_custom (catalog_paths, path, (GCompareFunc) g_strcmp0)))
	{
	  catalog_paths = g_list_remove_link (catalog_paths, l);
	}
}
