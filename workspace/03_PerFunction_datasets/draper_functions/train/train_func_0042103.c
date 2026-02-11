mx_icon_theme_load_fallbacks (MxIconTheme *theme,
                              GKeyFile    *theme_file,
                              gboolean     root)
{
  MxIconThemePrivate *priv = theme->priv;
  gchar *fallbacks = g_key_file_get_string (theme_file,
                                            "Icon Theme",
                                            "Inherits",
                                            NULL);


  if (!root)
    priv->theme_fallbacks = g_list_append (priv->theme_fallbacks,
                                           theme_file);


  if (fallbacks)
    {
      gint i = 0;
      gint fallbacks_len = strlen (fallbacks);

      g_strdelimit (fallbacks, ",", '\0');

      while (i < fallbacks_len)
        {
          gchar *fallback = fallbacks + i;
          i += strlen (fallback) + 1;


          if (g_str_equal (fallback, "hicolor"))
            continue;


          if (g_hash_table_find (priv->theme_path_hash,
                                 mx_icon_theme_find_name_cb,
                                 fallback))
            continue;


          theme_file = mx_icon_theme_load_theme (theme, fallback);
          if (theme_file)
            mx_icon_theme_load_fallbacks (theme, theme_file, FALSE);
        }
      g_free (fallbacks);
    }
}
