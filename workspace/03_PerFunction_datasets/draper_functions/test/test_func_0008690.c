ensure_theme_directories_exist ()
{
  const gchar *theme_dir;
  gboolean ret;

  theme_dir = unity_webapps_dirs_get_icon_theme_dir ();

  ret = TRUE;

  if (theme_dir_has_index (theme_dir) == FALSE)
    {
      ret = create_empty_theme (theme_dir);
    }

  return ret;
}
