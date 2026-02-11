save_geometry_to_file(gpointer user_data)
{
  gchar *data, *file;

  g_assert( dialog_geometry != NULL );

  data = g_key_file_to_data(dialog_geometry, NULL, NULL);
  file = g_build_filename(s_path_user_config (), DIALOG_GEOMETRY_STORE,
        NULL);
  g_file_set_contents(file, data, -1, NULL);
  g_free(data);
  g_free(file);
}
