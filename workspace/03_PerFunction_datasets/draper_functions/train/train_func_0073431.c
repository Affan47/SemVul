ggd_opt_group_load_from_file (GgdOptGroup  *group,
                              const gchar  *filename,
                              GError      **error)
{
  gboolean  success = FALSE;
  GKeyFile *key_file;

  key_file = g_key_file_new ();
  if (g_key_file_load_from_file (key_file, filename, 0, error)) {
    ggd_opt_group_load_from_key_file (group, key_file);
    success = TRUE;
  }
  g_key_file_free (key_file);

  return success;
}
