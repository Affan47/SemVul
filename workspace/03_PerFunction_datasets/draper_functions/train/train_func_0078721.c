parse_commandline(char *name, char *parameter) {
    CONF_TYPE type=CONF_FILE;

#ifdef USE_WIN32
    (void)parameter;
#endif
    if(!name) {
        configuration_file=
#ifdef CONFDIR
            CONFDIR
#ifdef USE_WIN32
            "\\"
#else
            "/"
#endif
#endif
            "stunnel.conf";
    } else if(!strcasecmp(name, "-help")) {
        parse_global_option(CMD_HELP, NULL, NULL);
        parse_service_option(CMD_HELP, NULL, NULL, NULL);
        log_flush(LOG_MODE_INFO);
        return 1;
    } else if(!strcasecmp(name, "-version")) {
        parse_global_option(CMD_DEFAULT, NULL, NULL);
        parse_service_option(CMD_DEFAULT, NULL, NULL, NULL);
        log_flush(LOG_MODE_INFO);
        return 1;
    } else if(!strcasecmp(name, "-sockets")) {
        print_socket_options();
        log_flush(LOG_MODE_INFO);
        return 1;
    } else
#ifndef USE_WIN32
    if(!strcasecmp(name, "-fd")) {
        if(!parameter) {
            s_log(LOG_ERR, "No file descriptor specified");
            print_syntax();
            return 1;
        }
        configuration_file=parameter;
        type=CONF_FD;
    } else
#endif
        configuration_file=name;
    configuration_file=str_dup(configuration_file);
    str_detach(configuration_file);

    if(parse_conf(type))
        return 1;
    apply_conf();
    return 0;
}
