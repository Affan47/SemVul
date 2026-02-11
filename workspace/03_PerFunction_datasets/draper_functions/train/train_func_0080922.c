filename_get_relative_path(gchar *filename){
  if (!filename || strlen(filename)==0) return g_strdup(".");
  GFile *file= g_file_new_for_commandline_arg(filename);
  GFile *home= g_file_new_for_commandline_arg((gchar *) g_get_home_dir());
  gchar *rel =g_file_get_relative_path (home,file);
  g_object_unref(file);
  g_object_unref(home);
  if (rel) {
  gchar *relpath=g_strdup_printf("~/%s",rel);
  g_free(rel);
  unquote(relpath);
  return relpath;
  }
  unquote(filename);
  return g_strdup(filename);
}
