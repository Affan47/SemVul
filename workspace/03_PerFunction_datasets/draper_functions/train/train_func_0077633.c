lfp_is_fd_nonblock (int fd)
{
    int current_flags = fcntl(fd, F_GETFL);
    if (current_flags < 0) {
        return -1;
    } else {
        return (current_flags & O_NONBLOCK) ? true : false;
    }
}
