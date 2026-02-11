gst_tag_parse_extended_comment (const gchar * ext_comment, gchar ** key,
    gchar ** lang, gchar ** value, gboolean fail_if_no_key)
{
  const gchar *div, *bop, *bcl;

  g_return_val_if_fail (ext_comment != NULL, FALSE);
  g_return_val_if_fail (g_utf8_validate (ext_comment, -1, NULL), FALSE);

  if (key)
    *key = NULL;
  if (lang)
    *lang = NULL;

  div = strchr (ext_comment, '=');
  bop = strchr (ext_comment, '[');
  bcl = strchr (ext_comment, ']');

  if (div == NULL) {
    if (fail_if_no_key)
      return FALSE;
    if (value)
      *value = g_strdup (ext_comment);
    return TRUE;
  }

  if (bop != NULL && bop < div) {
    if (bcl < bop || bcl > div)
      return FALSE;
    if (key)
      *key = g_strndup (ext_comment, bop - ext_comment);
    if (lang)
      *lang = g_strndup (bop + 1, bcl - bop - 1);
  } else {
    if (key)
      *key = g_strndup (ext_comment, div - ext_comment);
  }

  if (value)
    *value = g_strdup (div + 1);

  return TRUE;
}
