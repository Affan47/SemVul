run_one_game(server_data* server) {
    int status, maximum_fd, fd;
    int player_id;
    connection_data *connection;
    fd_set ready_fdset;

    connection = init_connection_data(server);

    while (1) {
        FD_ZERO(&ready_fdset);
        FD_SET(server->sock_fd, &ready_fdset);
        maximum_fd = server->sock_fd;
        prepare_fd_set(connection, &ready_fdset, &maximum_fd);

        status = handle_select(maximum_fd + 1, &ready_fdset, NULL, NULL);
        if (status <= 0)
            continue;
        log_debug("select returned %d", status);
        if (FD_ISSET(server->sock_fd, &ready_fdset)) {
            handle_new_client(connection);
            continue;
        }

        for (player_id = 0; player_id < MAX_CONNECTIONS; player_id++) {
            fd = connection->players[player_id].fd;
            if (FD_ISSET(fd, &ready_fdset)) {
                server_handle_incoming_connection(connection, player_id);
            }
        }

        if (is_game_over(connection))
            break;

    }

    close_all_connections(connection);
    free(connection);
}
