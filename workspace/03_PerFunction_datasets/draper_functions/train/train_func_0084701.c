make_theme_menu (void)
{
  gchar *dir;

  if (theme_list)
    g_object_unref (theme_list);

  dir = g_build_filename (DATA_DIRECTORY, "themes", NULL);
  theme_list = games_file_list_new_images (dir, NULL);
  g_free (dir);
  games_file_list_transform_basename (theme_list);


  return games_file_list_create_widget (theme_list,
					properties.themename,
					GAMES_FILE_LIST_REMOVE_EXTENSION |
					GAMES_FILE_LIST_REPLACE_UNDERSCORES);
}
