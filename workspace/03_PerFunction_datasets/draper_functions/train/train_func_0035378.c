_tpl_rmdir_recursively (const gchar *dir_name)
{
  GDir *dir;
  const gchar *name;

  dir = g_dir_open (dir_name, 0, NULL);


  if (dir == NULL)
    return;

  while ((name = g_dir_read_name (dir)) != NULL)
    {
      gchar *filename = g_build_path (G_DIR_SEPARATOR_S,
          dir_name, name, NULL);

      if (g_file_test (filename, G_FILE_TEST_IS_DIR))
        _tpl_rmdir_recursively (filename);
      else if (g_unlink (filename) < 0)
        g_warning ("Could not unlink '%s': %s", filename, g_strerror (errno));

      g_free (filename);
    }

  g_dir_close (dir);

  if (g_rmdir (dir_name) < 0)
    g_warning ("Could not remove directory '%s': %s",
        dir_name, g_strerror (errno));
}
