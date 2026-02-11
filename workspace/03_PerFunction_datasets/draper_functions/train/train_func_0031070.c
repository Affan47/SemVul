main(int argc, char **argv) {
    struct config config;
    struct instance instance = {
        .config = &config,
    };

    INIT_LIST_HEAD(&instance.connections);


    config_get(&config, argc, argv);

    log(1, "uoproxy v" VERSION
        ", http://max.kellermann.name/projects/uoproxy/\n");


    struct event_base *event_base = event_init();

    setup_signal_handlers(&instance);

    instance_setup_server_socket(&instance);

    instance_daemonize(&instance);


    event_dispatch();


    event_base_free(event_base);

    config_dispose(&config);

    return 0;
}
