text_decoration_to_string (StTextDecoration decoration)
{
  GString *result = g_string_new (NULL);

  if (decoration & ST_TEXT_DECORATION_UNDERLINE)
    g_string_append(result, " underline");
  if (decoration & ST_TEXT_DECORATION_OVERLINE)
    g_string_append(result, " overline");
  if (decoration & ST_TEXT_DECORATION_LINE_THROUGH)
    g_string_append(result, " line_through");
  if (decoration & ST_TEXT_DECORATION_BLINK)
    g_string_append(result, " blink");

  if (result->len > 0)
    g_string_erase (result, 0, 1);
  else
    g_string_append(result, "none");

  return g_string_free (result, FALSE);
}
