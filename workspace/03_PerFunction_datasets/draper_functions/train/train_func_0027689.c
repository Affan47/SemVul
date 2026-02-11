wpt_from_name(const char *args, const char **unused)
{
  if (wpt_from != NULL) {
    wpt_from->shortname = xstrappend(wpt_from->shortname, args);
  }
}
