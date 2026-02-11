exists(const char *path) {
  struct stat st;
  return stat(path, &st) != 0 ? 0 : S_ISDIR(st.st_mode)  == 0 ? 1 : 2;
}
