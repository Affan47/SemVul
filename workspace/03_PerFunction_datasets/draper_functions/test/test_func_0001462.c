dirchg (char *name, char *local)
{
  reg char *last;
  reg int len;
  auto char dir[PATHSIZE];

  if (*name != '/')
    return (warn (name, "Relative pathname"));
  for (last = name + strlen (name); last[-1] != '/'; --last)
    ;
  len = last - name;
  strncpy (dir, name, (size_t)len)[len] = '\0';
  VOID strcpy (local, *last ? last : ".");
  if (strcmp (dir, pwd) == 0)
    return (0);
  if (chdir (dir) < 0)
    return (warn (name, syserr ()));
  VOID strcpy (pwd, dir);
  return (0);
}
