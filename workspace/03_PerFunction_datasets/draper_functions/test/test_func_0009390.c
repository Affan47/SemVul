write (const void *data, int size)
{
    ssize_t nbytes = send (s, data, size, 0);


    if (nbytes == -1 && (errno == EAGAIN || errno == EINTR))
        return 0;


    if (nbytes == -1 && errno == ECONNRESET)
        return -1;

    errno_assert (nbytes != -1);
    return (size_t) nbytes;
}
