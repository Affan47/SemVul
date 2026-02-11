builder_path() {
  gchar *path;
#ifdef WIN32
  gchar *packagedir;
  packagedir = g_win32_get_package_installation_directory_utf8("glurp",NULL);
  debug("Got %s as package installation dir", packagedir);

  path = g_build_filename(packagedir,"data", "glurp.glade",NULL);
#else
  if (g_file_test("./glurp.glade", G_FILE_TEST_EXISTS)) return g_strdup("./glurp.glade");
  path = g_strdup_printf(DATA_DIR"glurp.glade");
#endif

  if(!g_file_test(path, G_FILE_TEST_EXISTS)) {
    debug("file '%s' does not exist", path);
    g_free(path);
    path = g_strdup("glurp.glade");
    if(!g_file_test(path, G_FILE_TEST_EXISTS)) {
      g_free(path);
      return NULL;
    } else {
      debug("found file '%s'", path);
      return path;
    }
  } else {
    debug("found file '%s'", path);
    return path;
  }
}
