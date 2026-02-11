wfff_wep(const char *args, const char **unused)
{
  if (args) {
    ap_wep = xstrdup(args);
  }
}
