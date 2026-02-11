config_get_commandlines(int argc, char **argv, config_line_t **result)
{
  config_line_t *front = NULL;
  config_line_t **new = &front;
  char *s;
  int i = 1;

  while (i < argc) {
    unsigned command = CONFIG_LINE_NORMAL;
    int want_arg = 1;

    if (!strcmp(argv[i],"-f") ||
        !strcmp(argv[i],"--defaults-torrc") ||
        !strcmp(argv[i],"--hash-password")) {
      i += 2;
      continue;
    } else if (!strcmp(argv[i],"--list-fingerprint") ||
               !strcmp(argv[i],"--verify-config") ||
               !strcmp(argv[i],"--ignore-missing-torrc") ||
               !strcmp(argv[i],"--quiet") ||
               !strcmp(argv[i],"--hush")) {
      i += 1;
      continue;
    } else if (!strcmp(argv[i],"--nt-service") ||
               !strcmp(argv[i],"-nt-service")) {
      i += 1;
      continue;
    }

    *new = tor_malloc_zero(sizeof(config_line_t));
    s = argv[i];


    if (*s == '-')
      s++;
    if (*s == '-')
      s++;

    if (*s == '+') {
      s++;
      command = CONFIG_LINE_APPEND;
    } else if (*s == '/') {
      s++;
      command = CONFIG_LINE_CLEAR;

      want_arg = 0;
    }

    if (want_arg && i == argc-1) {
      log_warn(LD_CONFIG,"Command-line option '%s' with no value. Failing.",
               argv[i]);
      config_free_lines(front);
      return -1;
    }

    (*new)->key = tor_strdup(expand_abbrev(&options_format, s, 1, 1));
    (*new)->value = want_arg ? tor_strdup(argv[i+1]) : tor_strdup("");
    (*new)->command = command;
    (*new)->next = NULL;
    log(LOG_DEBUG, LD_CONFIG, "command line: parsed keyword '%s', value '%s'",
        (*new)->key, (*new)->value);

    new = &((*new)->next);
    i += want_arg ? 2 : 1;
  }
  *result = front;
  return 0;
}
