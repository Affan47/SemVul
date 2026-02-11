__old_tmpfile (void)
{
  char buf[FILENAME_MAX];
  int fd;
  FILE *f;

  if (__path_search (buf, FILENAME_MAX, NULL, "tmpf", 0))
    return NULL;
  fd = __gen_tempname (buf, 0, 0, __GT_FILE);
  if (fd < 0)
    return NULL;


  (void) __unlink (buf);

  if ((f = _IO_old_fdopen (fd, "w+b")) == NULL)
    __close (fd);

  return f;
}
