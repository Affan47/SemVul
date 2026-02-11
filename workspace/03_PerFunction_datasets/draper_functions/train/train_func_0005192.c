write_args(char **vector, char *filename) {
  ssize_t i;
  int fd;
  char strings[10001];
  char *str = strings;

  if (-1 == (fd = mtcp_sys_open2(filename, O_RDONLY))) {
    MTCP_PRINTF("Error %d opening %s\n", filename, mtcp_sys_errno);
    mtcp_sys_exit(1);
  }
  strings[1000] = '\0';
  ssize_t num_read = mtcp_read_all(fd, strings, 10000);
  mtcp_sys_close(fd);

  if (num_read == -1)
    return -1;

  for (i = 0; str - strings < num_read && i < MAX_ARGS; i++) {
    vector[i] = str;
    while (*str++ != '\0')
      ;
  }
  vector[i] = NULL;
  return 0;
}
