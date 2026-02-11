compare_dir_entries(const void *p1, const void *p2) {
  const struct dir_entry *a = (const struct dir_entry *) p1,
        *b = (const struct dir_entry *) p2;
  const char *qs = a->conn->mg_conn.query_string ?
    a->conn->mg_conn.query_string : "na";
  int cmp_result = 0;

  if (S_ISDIR(a->st.st_mode) && !S_ISDIR(b->st.st_mode)) {
    return -1;
  } else if (!S_ISDIR(a->st.st_mode) && S_ISDIR(b->st.st_mode)) {
    return 1;
  } else if (*qs == 'n') {
    cmp_result = strcmp(a->file_name, b->file_name);
  } else if (*qs == 's') {
    cmp_result = a->st.st_size == b->st.st_size ? 0 :
      a->st.st_size > b->st.st_size ? 1 : -1;
  } else if (*qs == 'd') {
    cmp_result = a->st.st_mtime == b->st.st_mtime ? 0 :
      a->st.st_mtime > b->st.st_mtime ? 1 : -1;
  }

  return qs[1] == 'd' ? -cmp_result : cmp_result;
}
