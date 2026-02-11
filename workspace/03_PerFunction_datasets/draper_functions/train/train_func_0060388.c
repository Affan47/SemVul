priv_gst_structure_parse_name (gchar * str, gchar ** start, gchar ** end,
    gchar ** next)
{
  char *w;
  char *r;

  r = str;


  while (*r && (g_ascii_isspace (*r) || (r[0] == '\\'
              && g_ascii_isspace (r[1]))))
    r++;

  *start = r;

  if (G_UNLIKELY (!gst_structure_parse_string (r, &w, &r, TRUE))) {
    GST_WARNING ("Failed to parse structure string '%s'", str);
    return FALSE;
  }

  *end = w;
  *next = r;

  return TRUE;
}
