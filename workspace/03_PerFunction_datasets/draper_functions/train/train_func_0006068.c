dup_no_EINTR
   ___P((int fd),
        (fd)
int fd;)
{
  int result;

  for (;;)
    {
      result = dup (fd);
      if (result >= 0 || errno != EINTR)
        break;
    }

  return result;
}
