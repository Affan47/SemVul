lbcd_weight_init(const char *cmd, const char *service, int timeout)
{
    lbcd_command = cmd;
    lbcd_service = service;
    lbcd_timeout = timeout;


    if (service != NULL && is_weights(service) == 0) {
        char *cp;

        cp = strchr(service,':');
        *cp++ = '\0';
        default_weight = atoi(service);
        default_increment = atoi(cp);
        lbcd_default_functab = service_to_func("rr");
    }

    else if (cmd) {
        lbcd_default_functab = service_to_func("cmd");
    }

    else {

        default_weight = 1;
        default_increment = 1;


        lbcd_default_functab = service_to_func(service ? service : "load");
    }
    return 0;
}
