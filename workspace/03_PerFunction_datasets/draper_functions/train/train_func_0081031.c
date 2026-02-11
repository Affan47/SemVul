egg_desktop_file_new (const char *desktop_file_path, GError **error)
{
  GKeyFile *key_file;

  key_file = g_key_file_new ();
  if (!g_key_file_load_from_file (key_file, desktop_file_path, 0, error))
    {
      g_key_file_free (key_file);
      return NULL;
    }

  return egg_desktop_file_new_from_key_file (key_file, desktop_file_path,
					     error);
}
