nonblock_fcntl (int sock)
{
#ifdef	F_GETFL
    long fcntl_flags;

    fcntl_flags = fcntl (sock, F_GETFL, 0);
    if (fcntl_flags == -1)
    {
        logg ("nonblock_fcntl: saving: fcntl(%d, F_GETFL): errno=%d: %s\n",
              sock, errno, strerror (errno));
    }
    else if (fcntl (sock, F_SETFL, fcntl_flags | O_NONBLOCK))
    {
        logg ("nonblock_fcntl: fcntl(%d, F_SETFL, O_NONBLOCK): errno=%d: %s\n", sock, errno, strerror (errno));
    }

    return fcntl_flags;
#else
    return 0;
#endif
}
