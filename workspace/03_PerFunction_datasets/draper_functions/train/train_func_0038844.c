unlink_pidfile(int pid, char *file, u_int16 port)
{
  char *c;
  int ret;

  if (!(c = (char*)malloc(strlen(file)+16)))
    return -1;

  sprintf(c, "%s.%d", file, (int)port);

  if ((ret = unlink(c)) < 0)
    fterr_warn("unlink(%s)", c);

  free (c);

  return ret;

}
