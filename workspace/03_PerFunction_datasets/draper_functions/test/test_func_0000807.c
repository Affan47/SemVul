parse_color_name (GeglColor   *color,
                  const gchar *color_string)
{
  gsize i;

  for (i = 0; i < G_N_ELEMENTS (color_names); ++i)
    {
      if (g_ascii_strcasecmp (color_names[i].color_name, color_string) == 0)
        {
          memcpy (color->priv->rgba_color, color_names[i].rgba_color, sizeof (color_names[i].rgba_color));
          return TRUE;
        }
    }

  return FALSE;
}
