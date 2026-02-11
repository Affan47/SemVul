make_path(const char * parent, const char * relative_path) {
  size_t parent_length = strlen(parent);
  size_t relative_path_length = strlen(relative_path);
  size_t result_length = addst(parent_length, relative_path_length);
  int parent_ends_with_slash = parent_length > 0 && is_slash(parent[parent_length - 1]);
  if (parent_ends_with_slash) {
    result_length = addst(result_length, 1);
  }
  else {
    result_length = addst(result_length, 2);
  }
  char * result = xmalloc(result_length);
  strcpy(result, parent);
  char * p = result + parent_length;
  if (! parent_ends_with_slash) {
    *p = '/';
    ++p;
  }
  strcpy(p, relative_path);
  return result;
}
