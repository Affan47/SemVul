is_root (const char *filename)
{
  const char *p;

  p = filename;
  while (*p == '/')
    p++;

  return *p == 0;
}
