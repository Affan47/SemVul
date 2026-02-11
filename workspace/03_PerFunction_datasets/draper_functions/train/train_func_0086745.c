tool_file_format_new(const gchar* descr, const gchar** patterns)
{
  ToolFileFormat *format;

  g_return_val_if_fail(descr && descr[0] && patterns, (ToolFileFormat*)0);

  format = TOOL_FILE_FORMAT(g_object_new(TOOL_TYPE_FILE_FORMAT,
                                         "name", descr, "ignore-type", FALSE, NULL));
  tool_file_format_addPatterns(format, patterns);

  return format;
}
