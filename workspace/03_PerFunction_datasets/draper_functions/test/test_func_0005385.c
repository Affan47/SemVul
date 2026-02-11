ser_setspeed(union filedescriptor *fd, long baud)
{
  int rc;
  struct termios termios;
  speed_t speed = serial_baud_lookup (baud);

  if (!isatty(fd->ifd))
    return -ENOTTY;


  rc = tcgetattr(fd->ifd, &termios);
  if (rc < 0) {
    fprintf(stderr, "%s: ser_setspeed(): tcgetattr() failed",
            progname);
    return -errno;
  }


  if (! saved_original_termios++) {
    original_termios = termios;
  }

  termios.c_iflag = IGNBRK;
  termios.c_oflag = 0;
  termios.c_lflag = 0;
  termios.c_cflag = (CS8 | CREAD | CLOCAL);
  termios.c_cc[VMIN]  = 1;
  termios.c_cc[VTIME] = 0;

  cfsetospeed(&termios, speed);
  cfsetispeed(&termios, speed);

  rc = tcsetattr(fd->ifd, TCSANOW, &termios);
  if (rc < 0) {
    fprintf(stderr, "%s: ser_setspeed(): tcsetattr() failed\n",
            progname);
    return -errno;
  }


  rc = fcntl(fd->ifd, F_GETFL, 0);
  if (rc != -1)
    fcntl(fd->ifd, F_SETFL, rc & ~O_NONBLOCK);

  return 0;
}
