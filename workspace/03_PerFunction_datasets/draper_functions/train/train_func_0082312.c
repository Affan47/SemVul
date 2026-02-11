parse_client_commandline_arguments(int argc, char* argv[], client_data* client) {


    if (argc > 3) {
        log_error("invalid number of arguments");
        return 0;
    }

    if (argc >= 2) {
        client->server_address = strdup(argv[1]);
        if (argc == 3)
            client->server_port = strtol(argv[2], NULL, 10);
        else
            client->server_port = DEFAULT_PORT;
    } else {
        client->server_address = strdup(DEFAULT_SERVER);
        client->server_port = DEFAULT_PORT;
    }

    return 1;
}
