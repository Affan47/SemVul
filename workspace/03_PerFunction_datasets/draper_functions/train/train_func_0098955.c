read_entire_file (const char *mrl, ssize_t *file_size)
{
  char        *buf;
  struct stat  statb;
  int          fd;
  ssize_t      size;

  if (!strncasecmp (mrl, "http://", 7))
    return http_download (mrl, file_size);

  if (file_size)
    *file_size = 0;

  if (stat (mrl, &statb) < 0)
  {

    return NULL;
  }

  if (S_ISDIR (statb.st_mode))
  {
    errno = EISDIR;
    return NULL;
  }

  size = statb.st_size;

  fd = open (mrl, O_RDONLY);
  if (fd<0)
    return NULL;


  buf = malloc (size + 2);
  if (!buf)
  {
    close (fd);
    errno = ENOMEM;
    return NULL;
  }

  size = read (fd, buf, size);
  if (size < 0)
  {

    free (buf);
    size = errno;
    close (fd);
    errno = size;
    return NULL;
  }

  if (file_size)
    *file_size = size;

  if (size && buf[size - 1] != '\n')
    buf[size++] = '\n';
  buf[size] = 0;

  close (fd);

  return buf;
}
