http_write_header (int fd, Http_header *header)
{
  ssize_t n = 0, m;

  if (header == NULL)
    return write_all (fd, "\r\n", 2);

  m = write_all (fd, (void *)header->name, strlen (header->name));
  if (m == -1)
    {
      return -1;
    }
  n += m;

  m = write_all (fd, ": ", 2);
  if (m == -1)
    {
      return -1;
    }
  n += m;

  m = write_all (fd, (void *)header->value, strlen (header->value));
  if (m == -1)
    {
      return -1;
    }
  n += m;

  m = write_all (fd, "\r\n", 2);
  if (m == -1)
    {
      return -1;
    }
  n += m;

  m = http_write_header (fd, header->next);
  if (m == -1)
    {
      return -1;
    }
  n += m;

  return n;
}
