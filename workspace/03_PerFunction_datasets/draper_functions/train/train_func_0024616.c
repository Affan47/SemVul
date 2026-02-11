read_no_EINTR
   ___P((int fd,
         void *buf,
         size_t len),
        (fd,
         buf,
         len)
int fd;
void *buf;
size_t len;)
{
  char *p = ___CAST(char*,buf);
  ssize_t result = 0;
  int n;

  while (result < len)
    {
      n = read (fd, p+result, len-result);
      if (n > 0)
        result += n;
      else if (n == 0)
        break;
      else if (errno != EINTR)
        return n;
    }

  return result;
}
