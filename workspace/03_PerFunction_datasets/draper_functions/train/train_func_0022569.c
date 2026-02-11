compare_accept(char *line) {
  int rv = 0;
  char *tmp;
  if ((tmp = strchr(line, ';'))) *tmp = '\0';
  if (!strncmp(line, "image/", 6)) {
    rv |= 1;
    debugmsg(DEBUG_HTTP, "HTTP: accept image: %s\n", line);
  } else if (!strcmp(line, "*/*")) {
    rv |= 2;
    debugmsg(DEBUG_HTTP, "HTTP: accept all: %s\n", line);
  }
  if (tmp) *tmp = ';';
  return rv;
}
