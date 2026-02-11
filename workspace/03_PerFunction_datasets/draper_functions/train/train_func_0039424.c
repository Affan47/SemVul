nntp_write(struct nntp *nntp, const char *buffer, size_t length)
{
    ssize_t status;

    if (!nntp_flush(nntp))
        return false;
    status = xwrite(nntp->out_fd, buffer, length);
    return (status > 0);
}
