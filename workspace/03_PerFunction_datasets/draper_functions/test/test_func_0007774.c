set_system_parameter(char *path, char *entry, char *value) {
  char * completePath = NULL;
  FILE * file         = NULL;
  int    res          = 0;

  _OSBASE_TRACE(4,("--- set_system_parameter() called"));

  if (path == NULL || entry == NULL || value == NULL)
    return -1;
  completePath = (char *)malloc(strlen(path) + strlen(entry) + 1);
  if (completePath == NULL)
    return -1;
  sprintf(completePath, "%s/%s", path, entry);
  if ((file = fopen(completePath, "w")) == NULL)
    return -1;
  res = fwrite(value, 1, strlen(value), file);
  fclose(file);
  free(completePath);

  _OSBASE_TRACE(4,("--- set_system_parameter() exited"));
  return res;
}
