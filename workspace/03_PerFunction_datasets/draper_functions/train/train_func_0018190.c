scanHostPort(const char *str, char *host, int *port) {
  char *pos = strrchr(str, ':');

  if (pos != NULL) {
    int n = (int) (pos - str);

    if (n < 256) {
      host[0] = '\0';
      strncat(host, str, n);
      if (sscanf(pos + 1, "%d", port) == 1) {
        return 1;
      }
    }
  }
  return 0;
}
