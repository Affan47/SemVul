fosfat_symlink (fosfat_t *fosfat, const char *location)
{
  fosfat_bd_t *entry;
  char *link = NULL;

  if (!fosfat || !location)
    return NULL;

  entry = fosfat_search_insys (fosfat, location, S_BD);
  if (entry)
  {
    link = fosfat_get_link (fosfat, entry);
    free (entry);
  }

  if (!link)
    foslog (FOSLOG_ERROR, "target of symlink \"%s\" not found", location);

  return link;
}
