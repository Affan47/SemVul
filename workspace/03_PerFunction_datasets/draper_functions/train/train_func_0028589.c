FILE_get_ext(const char *path)
{
  const char *p;

  p = rindex(path, '/');
  if (p)
    path = &p[1];

  p = rindex(path, '.');
  if (p == NULL)
    return &path[strlen(path)];
  else
    return p + 1;
}
