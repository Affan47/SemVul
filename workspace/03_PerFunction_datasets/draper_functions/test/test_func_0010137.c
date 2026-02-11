visuPluginsParseDir(const gchar* path)
{
  GDir *gdir;
  const gchar *fileFromDir;
  GPatternSpec *pattern;
  GList* lst;

  lst = (GList*)0;
  gdir = g_dir_open(path, 0, NULL);
  if (!gdir)
    return lst;

  pattern = g_pattern_spec_new("lib*."G_MODULE_SUFFIX);
  fileFromDir = g_dir_read_name(gdir);
  while (fileFromDir)
    {
      if (g_pattern_match_string(pattern, fileFromDir))
	lst = g_list_prepend(lst, g_build_filename(path, fileFromDir, NULL));
      fileFromDir = g_dir_read_name(gdir);
    }
  g_dir_close(gdir);
  g_pattern_spec_free(pattern);

  return lst;
}
