logical_getcwd (void)
{
  struct stat st1;
  struct stat st2;
  char *wd = getenv ("PWD");
  char *p;


  if (!wd || wd[0] != '/')
    return NULL;
  p = wd;
  while ((p = strstr (p, "/.")))
    {
      if (!p[2] || p[2] == '/'
          || (p[2] == '.' && (!p[3] || p[3] == '/')))
        return NULL;
      p++;
    }


  if (stat (wd, &st1) == 0 && stat (".", &st2) == 0 && SAME_INODE (st1, st2))
    return wd;
  return NULL;
}
