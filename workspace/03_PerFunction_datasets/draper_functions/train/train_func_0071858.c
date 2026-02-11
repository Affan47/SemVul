exhcmd_set(struct he_s *hedit, char *args)
{
  char *p, *q, *option;
  enum s_option_e type;
  int no_f;
  char *skip;

  skip = exh_skipcmd(args, p = (char *)alloca(strlen(args) + 1));
  util_trunc(args = p);
  if (!*args) {
    char **list = s_option_value_list(), **i = list;
    if (*list) {
      tio_message(list, 1);
      press_any_key(hedit);
    } else
      he_message(0, "no options set");
    while (*i) free((char *)*i++);
    free((char *)list);
    return skip;
  }
  p = args;
  for (; *p;) {
    no_f = 0;
    option = q = p;
    while (*p && *p != ' ' && *p != '\t') ++p;
    if (*p) *p++ = 0;
    while (*p == ' ' || *p == '\t') ++p;
    if (!strncmp(option, "no", 2)) {
      option += 2;
      no_f = 1;
    } else {
      while (*q && *q != '=' && *q != ' ' && *q != '\t') ++q;
      if (*q == '=') {
        if (no_f) {
          he_message(0, "@Abinvalid argument:@~ %s", option);
          return skip;
        }
        *q = 0;
      } else
        q = 0;
    }
    if (!(type = s_get_type(option))) {
      he_message(0, "@Abinvalid option:@~ %s", option);
      return skip;
    }
    if (no_f && type != S_BOOL) {
      if (q) *q = '=';
      he_message(0, "@Abinvalid argument:@~ %s", option - 2);
      return skip;
    }
    if (q)
      s_set_option(option, q + 1, 0);
    else {
      if (type == S_BOOL)
        s_set_option(option, no_f ? "false" : "true", 0);
      else {
        char *value = s_get_option(option);
        if (!*value) value = "<unset>";
        he_message(0, "%s=%s@~", option, value);
      }
    }
  }
  return skip;
}
