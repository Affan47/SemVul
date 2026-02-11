log_store_xml_match_in_file (const gchar *filename,
    GRegex *regex)
{
  gboolean retval = FALSE;
  GMappedFile *file;
  gsize length;
  gchar *contents = NULL;

  file = g_mapped_file_new (filename, FALSE, NULL);
  if (file == NULL)
    goto out;

  length = g_mapped_file_get_length (file);
  contents = g_mapped_file_get_contents (file);

  if (length == 0 || contents == NULL)
    goto out;

  retval = g_regex_match_full (regex, contents, length, 0, 0, NULL, NULL);

  DEBUG ("%s pattern '%s' in file '%s'",
      retval ? "Matched" : "Not matched",
      g_regex_get_pattern (regex),
      filename);

out:
  if (file != NULL)
    g_mapped_file_unref (file);

  return retval;
}
