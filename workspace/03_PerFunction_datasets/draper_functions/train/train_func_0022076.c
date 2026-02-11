setup_keyfile ()
{
  if (dialog_geometry != NULL)
    return;

  gchar *file = g_build_filename (s_path_user_config (),
                                  DIALOG_GEOMETRY_STORE, NULL);

  dialog_geometry = g_key_file_new();


  gschem_atexit(save_geometry_to_file, NULL);

  if (!g_file_test (file, G_FILE_TEST_EXISTS)) {
    g_mkdir (s_path_user_config (), S_IRWXU | S_IRWXG);

    g_file_set_contents (file, "", -1, NULL);
  }

  if (!g_key_file_load_from_file (dialog_geometry, file, G_KEY_FILE_NONE, NULL)) {

    g_file_set_contents (file, "", -1, NULL);
    if ( !g_key_file_load_from_file (dialog_geometry, file, G_KEY_FILE_NONE, NULL)) {
       g_free (file);
       return;
    }
  }
  g_free (file);
}
