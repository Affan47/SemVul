mailstream_socket_open(int fd)
{
  mailstream_low * low;
  mailstream * s;

  low = mailstream_low_socket_open(fd);
  if (low == NULL)
    goto err;

  s = mailstream_new(low, 8192);
  if (s == NULL)
    goto free_low;

  return s;

 free_low:
  mailstream_low_close(low);
 err:
  return NULL;
}
