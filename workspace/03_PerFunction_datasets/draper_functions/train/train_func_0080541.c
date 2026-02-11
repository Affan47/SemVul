ares__read_line(FILE *fp, char **buf, size_t *bufsize)
{
  char *newbuf;
  size_t offset = 0;
  size_t len;

  if (*buf == NULL)
    {
      *buf = malloc(128);
      if (!*buf)
        return ARES_ENOMEM;
      *bufsize = 128;
    }

  for (;;)
    {
      int bytestoread = aresx_uztosi(*bufsize - offset);

      if (!fgets(*buf + offset, bytestoread, fp))
        return (offset != 0) ? 0 : (ferror(fp)) ? ARES_EFILE : ARES_EOF;
      len = offset + strlen(*buf + offset);
      if ((*buf)[len - 1] == '\n')
        {
          (*buf)[len - 1] = 0;
          break;
        }
      offset = len;
      if(len < *bufsize - 1)
        continue;


      newbuf = realloc(*buf, *bufsize * 2);
      if (!newbuf)
        return ARES_ENOMEM;
      *buf = newbuf;
      *bufsize *= 2;
    }
  return ARES_SUCCESS;
}
