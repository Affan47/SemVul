_set_from_xsettings (GParamSpec *pspec,
                     GValue     *value)
{
  gchar *font_string;
  gint font_size;
  PangoFontDescription *descr;
  MxSettings *settings = mx_settings_get_default ();
  gboolean result = FALSE;

  if (!strcmp (pspec->name, "font-family")
      || !strcmp (pspec->name, "font-size"))
    {
      const gchar *fn;
      PangoFontMask set_fields;

      g_object_get (settings, "font-name", &font_string, NULL);

      if (!font_string)
        return FALSE;

      descr = pango_font_description_from_string (font_string);
      g_free (font_string);

      set_fields = pango_font_description_get_set_fields (descr);


      if ((set_fields & PANGO_FONT_MASK_FAMILY)
          && !strcmp (pspec->name, "font-family")
          && G_VALUE_HOLDS_STRING (value))
        {
          fn = pango_font_description_get_family (descr);
          g_value_set_string (value, fn);
          result = TRUE;
        }

      else if ((set_fields & PANGO_FONT_MASK_SIZE)
               && !strcmp (pspec->name, "font-size")
               && G_VALUE_HOLDS_INT (value))
        {
          font_size = pango_font_description_get_size (descr) / PANGO_SCALE;
          if (!pango_font_description_get_size_is_absolute (descr))
            {
              ClutterBackend *backend = clutter_get_default_backend ();
              gdouble res = clutter_backend_get_resolution (backend);
              font_size = font_size * res / 72.0;
            }
          g_value_set_int (value, font_size);
          result = TRUE;
        }

      pango_font_description_free (descr);
      descr = NULL;
    }

  return result;
}
