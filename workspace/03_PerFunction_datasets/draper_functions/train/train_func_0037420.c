tempnam (const char *dir, const char *pfx)
{
  char buf[FILENAME_MAX];

  if (__path_search (buf, FILENAME_MAX, dir, pfx, 1))
    return NULL;

  if (__gen_tempname (buf, 0, 0, __GT_NOCREATE))
    return NULL;

  return __strdup (buf);
}
