libgnac_output_rename_pattern_new(const gchar pattern)
{
  g_return_val_if_fail(pattern, NULL);

  LibgnacRenamePattern *rename_pattern = g_malloc(sizeof(LibgnacRenamePattern));
  g_return_val_if_fail(rename_pattern, NULL);

  gchar *full_pattern = g_strdup_printf("%c%c",
      RENAME_PATTERN_SEPARATOR, pattern);

  rename_pattern->id = pattern;
  rename_pattern->replace = NULL;
  rename_pattern->regex = g_regex_new(full_pattern, G_REGEX_OPTIMIZE, 0, NULL);
  g_free(full_pattern);

  return rename_pattern;
}
