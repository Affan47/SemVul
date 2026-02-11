mx_icon_theme_get_icons (MxIconTheme *theme,
                         const gchar *icon_name)
{
  gint i;
  GIcon *icon;
  GList *data;

  const gchar * const *names = NULL;
  MxIconThemePrivate *priv = theme->priv;


  icon = g_themed_icon_new_with_default_fallbacks (icon_name);
  names = g_themed_icon_get_names (G_THEMED_ICON (icon));
  if (!names)
    {
      g_object_unref (icon);
      return NULL;
    }

  data = NULL;
  for (i = 0; names[i]; i++)
    {

      GIcon *single_icon = g_themed_icon_new (names[i]);
      gboolean success = g_hash_table_lookup_extended (priv->icon_hash,
                                                       single_icon,
                                                       NULL,
                                                       (gpointer *)&data);

      g_object_unref (single_icon);


      if (success && (i == 0))
        break;


      if (success)
        {


          if (data)
            data = mx_icon_theme_copy_data_list (data);
          g_hash_table_insert (priv->icon_hash, g_object_ref (icon), data);

          break;
        }


      if ((data = mx_icon_theme_load_icon (theme, names[i], icon)))
        break;
    }

  g_object_unref (icon);

  return data;
}
