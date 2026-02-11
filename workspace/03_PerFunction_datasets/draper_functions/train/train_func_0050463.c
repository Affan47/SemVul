fix_fds (void)
{


  int fd0 = open ("/dev/null", O_RDWR);
  int fd1 = open ("/dev/null", O_RDWR);
  int fd2 = open ("/dev/null", O_RDWR);
  if (fd0 > 2) close (fd0);
  if (fd1 > 2) close (fd1);
  if (fd2 > 2) close (fd2);
}
