get_option_index(const char *name) {
  int i;

  for (i = 0; config_options[i] != NULL; i += ENTRIES_PER_CONFIG_OPTION) {
    if (strcmp(config_options[i], name) == 0 ||
        strcmp(config_options[i + 1], name) == 0) {
      return i / ENTRIES_PER_CONFIG_OPTION;
    }
  }
  return -1;
}
