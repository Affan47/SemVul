conn_get_connecting_fds(fd_set *fds)
{
        Conn_t *conn;

        diag(COMPONENT, DIAG_DEBUG, "collecting connecting fds ");
        conn = connlist;
        while (conn) {
                if (conn->status == CONNECTING) {
                        FD_SET(conn->fd, fds);
                        diag(COMPONENT, DIAG_DEBUG, "%d", conn->fd);
                }
                conn = conn->next;
        }

}
