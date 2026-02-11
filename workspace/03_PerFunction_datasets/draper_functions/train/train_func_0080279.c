read_color(GdkColor *color, const char *text, gsize text_len, GError **error)
{
  gchar    *colordesc;
  int       idx;
  GdkColor  temp;

  copy_text(&colordesc, text, text_len);

  if (sscanf(colordesc, "%d %hu %hu %hu", &idx,
             &temp.red, &temp.green, &temp.blue) != 4) {
    g_set_error(error,
                G_MARKUP_ERROR, G_MARKUP_ERROR_PARSE,
                "Invalid color specification in config file.");
  }

  color[idx].red   = temp.red;
  color[idx].green = temp.green;
  color[idx].blue  = temp.blue;

  g_free(colordesc);
}
