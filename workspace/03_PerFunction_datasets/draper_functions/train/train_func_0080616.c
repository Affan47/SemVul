server_parse_conf(char *configfile) {
    server_t *server = NULL;
    json_value *json = NULL;
    json_settings settings = {0};
    int    fd;
    char   buf[10240];
    char   error[128];
    ssize_t sz;

    server = server_create();
    if (server == NULL) {
        return NULL;
    }

    fd = open(configfile, O_RDONLY);
    if (fd < 0) {
        error("Error opening config file");
        goto error;
    }
    sz = read(fd, buf, 10240);

    json = json_parse_ex(&settings, buf, sz, error);
    if (json == NULL) {
        error("Error parsing JSON config file: %s", error);
        goto error;
    } else if (json->type != json_object) {
        error("Invalid conf: the root is not a JSON object");
        goto error;
    }


    server->conf = json;

    if (_configure_server(server, json) != 0) {
        error("Error detected when configuring the server");
        goto error;
    }

    close(fd);
    return server;

    error:
    if (fd > 0) {
        close(fd);
    }
    if (json != NULL) {
        json_value_free(json);
        server->conf = NULL;
    }
    server_destroy(server);
    return NULL;
}
