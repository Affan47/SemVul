buffer_write(struct Buffer *buffer, int fd) {
    ssize_t bytes;
    struct iovec iov[2];

    bytes = writev(fd, iov, setup_read_iov(buffer, iov, 0));

    if (bytes > 0)
        advance_read_position(buffer, bytes);

    return bytes;
}
