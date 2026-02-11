catalogs_from_path (GList *catalogs, const gchar *path)
{
  GladeCatalog *catalog;
  GDir *dir;
  GError *error = NULL;
  const gchar *filename;

  if ((dir = g_dir_open (path, 0, &error)) != NULL)
    {
      while ((filename = g_dir_read_name (dir)))
        {
          gchar *catalog_filename;

          if (!g_str_has_suffix (filename, ".xml"))
            continue;


	  if (g_str_has_suffix (filename, ".gresource.xml"))
	    continue;

          catalog_filename = g_build_filename (path, filename, NULL);
          catalog = catalog_open (catalog_filename);
          g_free (catalog_filename);

          if (catalog)
            {


              if (!g_list_find_custom (catalogs, catalog->name,
                                       (GCompareFunc) catalog_find_by_name))
                catalogs = g_list_prepend (catalogs, catalog);
              else
                catalog_destroy (catalog);
            }
          else
            g_warning ("Unable to open the catalog file %s.\n", filename);
        }

      g_dir_close (dir);
    }
  else
    g_warning ("Failed to open catalog directory '%s': %s", path,
               error->message);


  return catalogs;
}
