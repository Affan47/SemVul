write_buffer (fd, buf, cnt)
     int fd;
     voidp buf;
     unsigned int cnt;
{
  if (INT_MAX < cnt)
    cnt = INT_MAX;
  return write (fd, buf, cnt);
}
