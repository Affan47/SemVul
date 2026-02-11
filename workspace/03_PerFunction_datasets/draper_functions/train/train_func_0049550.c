garcon_menu_lookup_directory (GarconMenu  *menu,
                              const gchar *filename)
{
  GarconMenuDirectory *directory = NULL;
  GList               *dirs = NULL;
  GList               *iter;
  GFile               *file;
  GFile               *dir;
  gboolean             found = FALSE;

  g_return_val_if_fail (GARCON_IS_MENU (menu), NULL);
  g_return_val_if_fail (filename != NULL, NULL);

  dirs = garcon_menu_get_directory_dirs (menu);


  for (iter = dirs; !found && iter != NULL; iter = g_list_next (iter))
    {
      dir = _garcon_file_new_relative_to_file (iter->data, menu->priv->file);
      file = _garcon_file_new_relative_to_file (filename, dir);


      if (G_LIKELY (g_file_query_exists (file, NULL)))
        {

          directory = garcon_menu_directory_new (file);


          found = TRUE;
        }


      g_object_unref (file);
      g_object_unref (dir);
    }


  g_list_free (dirs);

  return directory;
}
