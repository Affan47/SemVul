readn (int fd, void *buf, size_t buflen, size_t *nread)
{
  size_t nleft = buflen;
  int n;


  while (nleft > 0)
    {
#ifdef USE_GNU_PTH
# ifdef HAVE_W32_SYSTEM
#  error Cannot use pth_read here because it expects a system HANDLE.
# endif
      n = pth_read (fd, buf, nleft);
#else
      n = read (fd, buf, nleft);
#endif
      if (n < 0 && errno == EINTR)
        continue;
      if (n < 0)
        return -1;
      if (!n)
        break;
      nleft -= n;
      buf = (char*)buf + n;
    }
  if (nread)
    *nread = buflen - nleft;


  return 0;
}
