log_store_xml_create_filename_regex (gint type_mask)
{
  GString *pattern;
  GRegex *regex = NULL;
  GError *error = NULL;

  pattern = g_string_new ("");

  if (type_mask & TPL_EVENT_MASK_TEXT)
    g_string_append (pattern, LOG_FILENAME_PATTERN);

  if (type_mask & TPL_EVENT_MASK_CALL)
    g_string_append_printf (pattern,
        "%s" LOG_FILENAME_CALL_PATTERN,
        pattern->len == 0 ? "" : "|");

  if (pattern->len == 0)
    goto out;

  DEBUG ("Pattern is '%s'", pattern->str);

  regex = g_regex_new (pattern->str, G_REGEX_OPTIMIZE, 0, &error);

  if (regex == NULL)
    {
      DEBUG ("Failed to create regex: %s", error->message);
      g_error_free (error);
    }

out:
  g_string_free (pattern, TRUE);

  return regex;
}
