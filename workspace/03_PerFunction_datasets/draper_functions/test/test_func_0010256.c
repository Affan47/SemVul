xml_consider_ignoring(const char *t)
{
  const char **il;

  if (!xg_ignore_taglist) {
    return 0;
  }

  for (il = xg_ignore_taglist; *il; il++) {
    if (0 == strcmp(*il, t)) {
      return 1;
    }
  }
  return 0;
}
