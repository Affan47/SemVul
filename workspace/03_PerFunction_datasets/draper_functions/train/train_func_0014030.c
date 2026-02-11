get_icon_name (const gchar *mime_type)
{
  static gboolean first_call = TRUE;
  gchar *name = NULL;
  gchar *s;

  if (first_call)
    {
      g_warning ("%s: Replace by g_content_type_get_icon "
                 "when GVFS is merged into GLib.", G_STRLOC);
      first_call = FALSE;
    }

  if (mime_type)
    {
      name = g_strconcat ("gnome-mime-", mime_type, NULL);

      for(s = name; *s; ++s)
        {
          if (!isalpha (*s) || !isascii (*s))
            *s = '-';
        }
    }

  if (!name ||
      !gtk_icon_theme_has_icon (gtk_icon_theme_get_default (), name))
    {
      g_free (name);
      name = g_strdup ("gnome-mime-image");
    }

  return name;
}
