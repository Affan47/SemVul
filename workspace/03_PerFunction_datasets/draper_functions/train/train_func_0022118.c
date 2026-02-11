ExtractUntilChar(char *text, int c, char **endptr) {
  CHECK_NE(text, NULL);
  CHECK_NE(endptr, NULL);
  char *found;
  found = strchr(text, c);
  if (found == NULL) {
    *endptr = NULL;
    return false;
  }

  *endptr = found;
  *found = '\0';
  return true;
}
