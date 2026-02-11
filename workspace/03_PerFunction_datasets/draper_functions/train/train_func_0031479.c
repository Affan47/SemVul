create_cache_dir (const gchar *dir_name)
{

  if (dir_name)
    {
      if (g_mkdir_with_parents (dir_name, 0700) == -1 && errno != EEXIST)
        {
          g_warning ("Unable to create the image cache path '%s': %s",
              dir_name, g_strerror (errno));
          return FALSE;
        }
    }
  return TRUE;
}
