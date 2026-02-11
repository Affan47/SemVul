path_get_data_filename(const gchar * filename)
{
  gchar * full_path;
  struct stat st;

  path_check_initialization();


  full_path = g_strdup_printf("%s/../%s", pszPathToExecutable, filename);
  if (stat(full_path, &st) == 0)
  {
    return full_path;
  }
  g_free(full_path);

#if defined(DATA_DIR)

  full_path = g_strdup_printf(DATA_DIR "/%s", filename);
  if (stat(full_path, &st) == 0)
  {
    return full_path;
  }
  g_free(full_path);
#endif

  return NULL;
}
