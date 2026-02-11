read_buf (int fdes, char **buf)
{
  char *readloc;
  int n;
  int nread = 0;
  int size = 1;
  int grow = 2;

  *buf = emalloc(size);
  readloc = *buf;
  while (1) {
    n = read (fdes, readloc, size - nread);
    if (n == 0)
      break;
    if (n == -1)
      eprintf ("Error in read_buf:", __FILE__, __LINE__);

    nread += n;
    size *= grow;
    *buf = erealloc (*buf,size);
    readloc = *buf + nread;
  }

  return nread;
}
