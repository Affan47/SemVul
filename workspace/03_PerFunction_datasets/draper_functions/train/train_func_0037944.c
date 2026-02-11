main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./ev_httpd port\n");
        return -1;
    }
    int ret;
    ev_loop_t *loop;
    int listen_sock;

    listen_sock = ev_listen(atoi(argv[1]));
    if (listen_sock == -1) {
        return -1;
    }

    loop = ev_create_loop();
    ev_io_init(loop, 1024, 0);
    ret = ev_io_register(loop, listen_sock, EV_READ,  cb_accept, NULL);
    if (ret == -1) {
        fprintf(stderr, "register listen sock error\n");
        return -1;
    }
    printf("ev_httpd started successfully!\n");
    ev_run_loop(loop);
    return 0;
}
