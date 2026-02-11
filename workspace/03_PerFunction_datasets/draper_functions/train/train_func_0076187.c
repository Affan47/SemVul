path_merge(str* path, const char* start)
{

  if (*start == '/')
    if (!str_copys(path, "/")) return 0;

  while (*start) {
    const char* end;
    while (*start == '/') ++start;
    if ((end = strchr(start, '/')) != 0) {
      if (!path_merge_part(path, start, end - start)) return 0;
      start = end + 1;
    }
    else {
      if (!path_merge_part(path, start, strlen(start))) return 0;
      break;
    }
  }
  return 1;
}
