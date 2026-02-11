exh_map(struct he_s *hedit, char *args, int map)
{
  char *from, *to;
  char *p, *skip;

  skip = exh_skipcmd(args, p = (char *)alloca(strlen(args) + 1));
  args = p;
  if (!*args) {
    char **list, **i;
    i = list = tio_maplist(map);
    if (*list) {
      tio_message(list, 1);
      press_any_key(hedit);
    } else
      he_message(0, "no mappings");
    while (*i) free((char *)*i++);
    free((char *)list);
    return skip;
  }
  for (p = from = args; *p && *p != ' '; ++p);
  if (*p) {
    *p++ = 0;
    while (*p == ' ') ++p;
    for (to = p; *p; ++p);
    *p = 0;
    tio_map(map, from, to, he_map_special);
  }
  return skip;
}
