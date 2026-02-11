amide_gnome_program_locate_help_file (const gchar *file_name, gboolean only_if_exists) {

  gchar *buf;
  gchar ** retvals;
  gchar ** dirs;
  const gchar * const * global_dirs;
  gint i;
  gint j;
  gint count=0;
  gint slots;

  g_return_val_if_fail (file_name != NULL, NULL);

  global_dirs = g_get_system_data_dirs();
  while (global_dirs[count] != NULL) count++;


#if defined (G_PLATFORM_WIN32)
  slots = count+3;
#else
  slots = count+2;
#endif

  dirs = g_try_new0(gchar *,slots);
  retvals = g_try_new0(gchar *,slots);
  g_return_val_if_fail((dirs != NULL) && (retvals != NULL), NULL);

  j=0;

  dirs[j] = g_strdup(AMIDE_DATADIR);
  j++;


  i=0;
  while (global_dirs[i] != NULL) {
    dirs[j] = g_strdup(global_dirs[i]);
    i++;
    j++;
  }


  if (g_path_is_absolute (file_name))
    if (!only_if_exists || g_file_test (file_name, G_FILE_TEST_EXISTS)) {
      retvals[0] = g_strdup(file_name);
      return retvals;
    }


  if (AMIDE_DATADIR == NULL) {
    g_warning (G_STRLOC ": Directory properties not set correctly.  "
	       "Cannot locate application specific files.");
    return retvals;
  }

  i=0;
  j=0;
  while (dirs[i] != NULL) {
    buf = g_strdup_printf ("%s%s%s%s%s%s%s", dirs[i], G_DIR_SEPARATOR_S,"gnome",G_DIR_SEPARATOR_S, "help", G_DIR_SEPARATOR_S,file_name);

    if (!only_if_exists || g_file_test (buf, G_FILE_TEST_EXISTS)) {
      retvals[j] = buf;
      j++;
    } else
      g_free(buf);
    i++;
  }

  i=0;
  while (dirs[i] != NULL) {
    g_free(dirs[i]);
    i++;
  }
  g_free(dirs);

  return retvals;
}
