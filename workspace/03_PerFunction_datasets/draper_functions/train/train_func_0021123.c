clutter_config_read (void)
{
  gchar *config_path;

  config_path = g_build_filename (CLUTTER_SYSCONFDIR,
                                  "clutter-1.0",
                                  "settings.ini",
                                  NULL);
  if (g_file_test (config_path, G_FILE_TEST_EXISTS))
    clutter_config_read_from_file (config_path);

  g_free (config_path);

  config_path = g_build_filename (g_get_user_config_dir (),
                                  "clutter-1.0",
                                  "settings.ini",
                                  NULL);
  if (g_file_test (config_path, G_FILE_TEST_EXISTS))
    clutter_config_read_from_file (config_path);

  g_free (config_path);
}
