service_udp_fd(krb5_context context, struct conn_state *conn,
               struct select_state *selstate, int ssflags)
{
    int nread;

    if (!(ssflags & (SSF_READ|SSF_EXCEPTION)))
        abort();
    if (conn->state != READING)
        abort();

    nread = recv(conn->fd, conn->x.in.buf, conn->x.in.bufsize, 0);
    if (nread < 0) {
        TRACE_SENDTO_KDC_UDP_ERROR_RECV(context, &conn->addr, SOCKET_ERRNO);
        kill_conn(conn, selstate);
        return 0;
    }
    conn->x.in.pos = conn->x.in.buf + nread;
    return 1;
}
