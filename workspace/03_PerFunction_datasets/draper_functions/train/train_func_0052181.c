loadAll(const char *filepath, const char *pattern) {
  struct dirent **dir;
  int i, n = fl_filename_list(filepath, &dir);
  for (i=0; i<n; i++) {
    struct dirent *e = dir[i];
    if (pattern==0 || fl_filename_match(e->d_name, pattern)) {
      load(Fl_Preferences::Name("%s%s", filepath, e->d_name));
    }
    free(e);
  }
  free(dir);
  return 0;
}
