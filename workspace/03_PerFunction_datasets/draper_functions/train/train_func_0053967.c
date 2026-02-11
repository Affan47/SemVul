handle_new_connection(struct lwpb_transport_socket_server *socket_server)
{
    int socket;
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);
    char tmp[16];
    struct sockaddr_in *addr_in;
    int i;
    const char msg[] = "No more connections allowed\n";

    socket = accept(socket_server->socket, (struct sockaddr *) &addr, &len);
    if (socket < 0) {
        LWPB_ERR("Accepting new socket failed (errno: %d)", errno);
        return;
    }

    make_nonblock(socket);

    for (i = 0; i < LWPB_TRANSPORT_SOCKET_SERVER_CONNS; i++) {
        struct lwpb_socket_server_conn *conn = &socket_server->conns[i];
        if (conn->socket == -1) {
            addr_in = (struct sockaddr_in *) &addr;
            inet_ntop(addr.ss_family, &addr_in->sin_addr, tmp, sizeof(tmp));
            LWPB_DEBUG("Client(%d) accepted conncetion from %s", conn->index, tmp);
            conn->socket = socket;
            if (!conn->buf)
                lwpb_transport_alloc_buf(&socket_server->super, &conn->buf, &conn->len);
            conn->pos = conn->buf;
            socket_server->num_conns++;
            return;
        }
    }


    LWPB_DEBUG("No more connections allowed");
    send(socket, msg, sizeof(msg), 0);
    close(socket);
}
