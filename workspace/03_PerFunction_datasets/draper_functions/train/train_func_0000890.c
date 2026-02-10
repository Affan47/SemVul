config_param_val_bool (char *val, int *res) {
  if (val == NULL) return 0;
  if (
    strcasecmp(val, CFG_BOOL_ON) == 0 ||
    strcasecmp(val, "yes") == 0 ||
    strcasecmp(val, "y") == 0 ||
    strcasecmp(val, "true") == 0 ||
    strcasecmp(val, "t") == 0 ||
    strcasecmp(val, "1") == 0) {
    *res = 1;
  }

  return 1;
}
