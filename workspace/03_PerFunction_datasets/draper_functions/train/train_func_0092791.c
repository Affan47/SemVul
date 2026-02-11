dconf_engine_open_profile_file (const gchar *profile)
{
  const gchar * const *xdg_data_dirs;
  const gchar *prefix = "/etc";
  FILE *fp;

  xdg_data_dirs = g_get_system_data_dirs ();


  do
    {
      gchar *filename;
      const gchar *dconf_dir;

      dconf_dir = g_getenv ("DCONF_DIR");
      if (dconf_dir == NULL)
        filename = g_build_filename (prefix, "dconf/profile", profile, NULL);
      else
        filename = g_build_filename (dconf_dir, "profile", profile, NULL);
      fp = fopen (filename, "r");


      if (fp == NULL && errno != ENOENT)
        {
          g_warning ("Unable to open %s: %s", filename, g_strerror (errno));
          g_free (filename);
          return NULL;
        }

      g_free (filename);
    }
  while (fp == NULL && (prefix = *xdg_data_dirs++));


  return fp;
}
