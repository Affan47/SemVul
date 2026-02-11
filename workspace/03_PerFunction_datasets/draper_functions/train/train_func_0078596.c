tty_off_xon_xoff(int fd)
{
    struct termios buf;

    if (tcgetattr(fd, &buf) < 0)
        return -1;


    buf.c_iflag &= ~(IXON | IXOFF);
#ifdef IXANY
    buf.c_iflag &= ~IXANY;
#endif

    if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
        return -1;

    return 0;
}
