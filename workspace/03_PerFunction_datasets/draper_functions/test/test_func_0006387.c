hts_findfirst(char *path) {
  if (path) {
    if (strnotempty(path)) {
      find_handle_struct *find =
        (find_handle_struct *) calloc(1, sizeof(find_handle_struct));
      if (find) {
        memset(find, 0, sizeof(find_handle_struct));
#ifdef _WIN32
        {
          char BIGSTK rpath[1024 * 2];

          strcpybuff(rpath, path);
          if (rpath[0]) {
            if (rpath[strlen(rpath) - 1] != '\\')
              strcatbuff(rpath, "\\");
          }
          strcatbuff(rpath, "*.*");
          find->handle = FindFirstFileA(rpath, &find->hdata);
          if (find->handle != INVALID_HANDLE_VALUE)
            return find;
        }
#else
        strcpybuff(find->path, path);
        {
          if (find->path[0]) {
            if (find->path[strlen(find->path) - 1] != '/')
              strcatbuff(find->path, "/");
          }
        }
        find->hdir = opendir(path);
        if (find->hdir != NULL) {
          if (hts_findnext(find) == 1)
            return find;
        }
#endif
        free((void *) find);
      }
    }
  }
  return NULL;
}
