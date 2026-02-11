get_log_dir(cmd_parms *cmd, void *dconfig, const char *value) {
  if (value != NULL && value[0] != 0) {
    if (log_dir != NULL)
      free(log_dir);
    log_dir = strdup(value);
  }

  return NULL;
}
