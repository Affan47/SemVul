printtype (u_int mode)
{
  switch (mode & S_IFMT)
    {
    case S_IFDIR:
      putchar ('/');
      return (1);
    case S_IFIFO:
      putchar ('|');
      return (1);
    case S_IFLNK:
      putchar ('@');
      return (1);
    case S_IFSOCK:
      putchar ('=');
      return (1);
    }
  if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
    {
      putchar ('*');
      return (1);
    }
  return (0);
}
