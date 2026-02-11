makeraw (const char *channel, int fd)
{
  struct termios tt;

  if (tcgetattr (fd, &tt) == -1) {
    fprintf (stderr, "tcgetattr: ");
    perror (channel);
    return;
  }

  cfmakeraw (&tt);
  if (tcsetattr (fd, TCSANOW, &tt) == -1) {
    fprintf (stderr, "tcsetattr: ");
    perror (channel);
  }
}
