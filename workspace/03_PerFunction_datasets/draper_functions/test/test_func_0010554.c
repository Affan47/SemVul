com_set_dtr(int fd, unsigned char on)
{
    int flags;

    if (ioctl (fd, TIOCMGET, &flags) < 0)
    {
        perror ("ERROR: could not reset, getting V24 line status failed");
        return;
    }
    if (on)
    {
        flags |=  TIOCM_DTR;
    }
    else
    {
        flags &= ~TIOCM_DTR;
    }
    if (ioctl (fd, TIOCMSET, &flags) < 0)
    {
        perror ("ERROR: could not reset, setting V24 line status failed");
    }
}
