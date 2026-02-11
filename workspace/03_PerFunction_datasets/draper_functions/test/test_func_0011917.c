games_file_list_new_internal (const gchar * glob, va_list path)
{
  GPatternSpec *filespec = g_pattern_spec_new (glob);
  gchar *pathelement;
  GList *list = NULL;
  GDir *dir;
  const gchar *filename;
  gchar *fullname;

  while ((pathelement = va_arg (path, gchar *)) != NULL) {
    dir = g_dir_open (pathelement, 0, NULL);
    if (dir != NULL) {
      while ((filename = g_dir_read_name (dir)) != NULL) {
	if (g_pattern_match_string (filespec, filename)) {
	  fullname = g_build_filename (pathelement, filename, NULL);
	  if (g_file_test (fullname, G_FILE_TEST_IS_REGULAR)) {
	    list = g_list_append (list, fullname);
	  } else
	    g_free (fullname);
	}
      }
      g_dir_close (dir);
    }
  }

  g_pattern_spec_free (filespec);

  return list;
}
