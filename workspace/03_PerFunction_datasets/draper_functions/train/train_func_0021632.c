put_dir(const char *path) {
  char buf[MAX_PATH_SIZE];
  const char *s, *p;
  file_stat_t st;


  for (s = p = path + 1; (p = strchr(s, '/')) != NULL; s = ++p) {
    if (p - path >= (int) sizeof(buf)) return -1;
    memcpy(buf, path, p - path);
    buf[p - path] = '\0';
    if (stat(buf, &st) != 0 && mkdir(buf, 0755) != 0) return -1;
    if (p[1] == '\0') return 0;
  }

  return 1;
}
