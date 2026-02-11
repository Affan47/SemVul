_gftp_tty_raw (int fd)
{
  struct termios buf;

  if (tcgetattr (fd, &buf) < 0)
    return (-1);

  buf.c_iflag |= IGNPAR;
  buf.c_iflag &= ~(ICRNL | ISTRIP | IXON | IGNCR | IXANY | IXOFF | INLCR);
  buf.c_lflag &= ~(ECHO | ICANON | ISIG | ECHOE | ECHOK | ECHONL);
#ifdef IEXTEN
  buf.c_lflag &= ~(IEXTEN);
#endif

  buf.c_oflag &= ~(OPOST);
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;

  if (tcsetattr (fd, TCSADRAIN, &buf) < 0)
    return (-1);
  return (0);
}
