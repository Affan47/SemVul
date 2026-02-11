tty_cbreak(int fd, struct termios *orig)
{
    struct termios buf;

    if (tcgetattr(fd, &buf) < 0)
        return -1;


    *orig = buf;

    buf.c_lflag &= ~(ECHO | ICANON);
    buf.c_iflag &= ~(ICRNL | INLCR);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;

#if defined (VLNEXT) && defined (_POSIX_VDISABLE)
    buf.c_cc[VLNEXT] = _POSIX_VDISABLE;
#endif

#if defined (VDSUSP) && defined (_POSIX_VDISABLE)
    buf.c_cc[VDSUSP] = _POSIX_VDISABLE;
#endif

    if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
        return -1;

    return 0;
}
