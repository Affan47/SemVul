validate_ports_csv(smartlist_t *sl, const char *name, char **msg)
{
  int i;
  tor_assert(name);

  if (!sl)
    return 0;

  SMARTLIST_FOREACH(sl, const char *, cp,
  {
    i = atoi(cp);
    if (i < 1 || i > 65535) {
      tor_asprintf(msg, "Port '%s' out of range in %s", cp, name);
      return -1;
    }
  });
  return 0;
}
