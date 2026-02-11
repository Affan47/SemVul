com_drain (int fd)
{
    if (bytetime)
    {
        usleep (bytetime * waitcount);
        waitcount = 0;
    }
    else
    {
        while ((tcdrain(fd) < 0) && (errno == EINTR));
    }
}
