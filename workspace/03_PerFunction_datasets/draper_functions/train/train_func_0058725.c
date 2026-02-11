check_dev_tty ()
{
  int tty_fd;
  char *tty;

  tty_fd = open ("/dev/tty", O_RDWR|O_NONBLOCK);

  if (tty_fd < 0)
    {
      tty = (char *)ttyname (fileno (stdin));
      if (tty == 0)
	return;
      tty_fd = open (tty, O_RDWR|O_NONBLOCK);
    }
  close (tty_fd);
}
