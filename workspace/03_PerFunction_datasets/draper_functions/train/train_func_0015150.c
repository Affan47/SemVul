sqlboxc_run(void *arg)
{
    int fd;
    int port;


    gwthread_create(sql_to_bearerbox, NULL);

    port = (int)arg;

    fd = make_server_socket(port, NULL);


    if (fd < 0) {
        panic(0, "Could not open sqlbox port %d", port);
    }


    wait_for_connections(fd, run_sqlbox, NULL);


    close(fd);
}
