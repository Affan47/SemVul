mime_add_fcache(
    cups_array_t *filtercache,
    const char   *name,
    const char   *filterpath)
{
  _mime_fcache_t	key,
			*temp;
  char			path[1024];


  DEBUG_printf(("2mime_add_fcache(filtercache=%p, name=\"%s\", "
                "filterpath=\"%s\")", filtercache, name, filterpath));

  key.name = (char *)name;
  if ((temp = (_mime_fcache_t *)cupsArrayFind(filtercache, &key)) != NULL)
  {
    DEBUG_printf(("3mime_add_fcache: Returning \"%s\".", temp->path));
    return (temp->path);
  }

  if ((temp = calloc(1, sizeof(_mime_fcache_t))) == NULL)
  {
    DEBUG_puts("3mime_add_fcache: Returning NULL.");
    return (NULL);
  }

  temp->name = strdup(name);

  if (cupsFileFind(name, filterpath, 1, path, sizeof(path)))
    temp->path = strdup(path);

  cupsArrayAdd(filtercache, temp);

  DEBUG_printf(("3mime_add_fcache: Returning \"%s\".", temp->path));
  return (temp->path);
}
