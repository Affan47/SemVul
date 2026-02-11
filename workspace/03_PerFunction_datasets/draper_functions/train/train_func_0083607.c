ra_process(struct ra_server *server) {
    struct connection *connection, *next;
    if(ra_select(RA)) {
        ra_accept(RA);
    }
    next = RA->connections.active;
    while((connection = next)) {
        int action = 0;
        next = connection->next;
        if(ra_handle(RA, connection) == 0) {
            if(connection->next) {
                connection->next->prev = connection->prev;
            }
            if(connection->prev) {
                connection->prev->next = connection->next;
            } else {
                RA->connections.active = connection->next;
            }
            connection->next = RA->connections.free;
            RA->connections.free = connection;
        }
    }
}
