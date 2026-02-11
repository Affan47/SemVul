execvpe_(const char *cmd, char *const *argv, char *const *envp){
  char *path = NULL;
  const char *searchpath;
  const char *sep;
  size_t cmd_len;

  if (cmd[0] == '/')
    execve(cmd, argv, envp);

  searchpath = getenv("PATH");
  if (searchpath == NULL)
    searchpath = "/bin:/usr/bin";

  cmd_len = strlen(cmd);

  sep = NULL;
  do {
    size_t prefix_len, path_len;

    sep = strchr(searchpath, ':');
    if (sep == NULL) {
      sep = searchpath + strlen(searchpath);
    }

    prefix_len = (sep - searchpath);
    path_len = prefix_len + cmd_len + 2;
    path = realloc(path, path_len);
    if (path == NULL) {
      errno = ENOMEM;
      return -1;
    }
    memcpy(path, searchpath, prefix_len);
    if (prefix_len == 0 || searchpath[prefix_len - 1] == '/') {
      memcpy(path + prefix_len, cmd, cmd_len + 1);
    } else {
      path[prefix_len] = '/';
      memcpy(path + prefix_len + 1, cmd, cmd_len + 1);
    }

    execve(path, argv, envp);
    switch (errno) {
    case E2BIG:
    case ENOEXEC:
    case ENOMEM:
    case ETXTBSY:
      break;
    }

    searchpath = sep + 1;
  } while (sep[0] != '\0');

  if (path) free(path);

  return -1;
}
