spif_socket_check_io(spif_socket_t self)
{
    static struct timeval tv = { 0, 0 };
    fd_set read_fds, write_fds;

    ASSERT_RVAL(!SPIF_SOCKET_ISNULL(self), FALSE);
    REQUIRE_RVAL(self->fd >= 0, FALSE);

    FD_ZERO(&read_fds);
    FD_SET(self->fd, &read_fds);
    FD_ZERO(&write_fds);
    FD_SET(self->fd, &write_fds);
    if ((select(self->fd + 1, &read_fds, &write_fds, NULL, &tv)) < 0) {
        libast_print_error("Unable to select() on %d -- %s\n", self->fd, strerror(errno));
        return FALSE;
    }

    if (FD_ISSET(self->fd, &read_fds)) {
        SPIF_SOCKET_FLAGS_SET(self, SPIF_SOCKET_FLAGS_HAVE_INPUT);
    } else {
        SPIF_SOCKET_FLAGS_CLEAR(self, SPIF_SOCKET_FLAGS_HAVE_INPUT);
    }
    if (FD_ISSET(self->fd, &write_fds)) {
        SPIF_SOCKET_FLAGS_SET(self, SPIF_SOCKET_FLAGS_CAN_OUTPUT);
    } else {
        SPIF_SOCKET_FLAGS_CLEAR(self, SPIF_SOCKET_FLAGS_CAN_OUTPUT);
    }
    return TRUE;
}
