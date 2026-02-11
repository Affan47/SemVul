send_to_network(int file_descriptor, void *buffer, int buffer_size) {
    int status, done = 0, nbytes;
    fd_set write_file_descriptors;
    fd_set all_connections;
    struct timeval select_timeout;

    memset(&select_timeout, 0, sizeof(select_timeout));
    select_timeout.tv_sec = 0;
    select_timeout.tv_usec = 500;

    FD_ZERO(&all_connections);
    FD_SET(file_descriptor, &all_connections);

    fcntl(file_descriptor, F_SETFL, O_NONBLOCK);

    while (!done) {
        write_file_descriptors = all_connections;
        if ((status = select(file_descriptor + 1, NULL, &write_file_descriptors, NULL, &select_timeout)) == -1) {
            log_error("select failed");
            return 0;
        }
        if (FD_ISSET(file_descriptor, &write_file_descriptors)) {
            if ((nbytes = send(file_descriptor, buffer, buffer_size, 0)) <= 0) {
                if (nbytes == 0) {
                    log_debug("client hung up");
                } else {
                    log_error("send error");
                }
                close(file_descriptor);
            }
            done = 1;
        }
    }
    return nbytes;
}
