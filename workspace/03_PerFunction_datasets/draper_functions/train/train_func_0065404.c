get_themed_resource_path (const gchar *icon_name)
{
  GtkIconTheme *theme;
  GtkIconInfo *info;
  gchar *icon_path;

  if (icon_name == NULL)
    return NULL;

  theme = gtk_icon_theme_get_default ();
  UNITY_WEBAPPS_NOTE (RESOURCE, "Resource factory looking up icon name: %s", icon_name);

  info = gtk_icon_theme_lookup_icon (theme, icon_name, 48, 0);

  if (info == NULL)
    {
      return NULL;
    }

  icon_path = g_strdup (gtk_icon_info_get_filename (info));

  gtk_icon_info_free (info);

  return icon_path;
}
