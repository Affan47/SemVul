dns_engine_setarg(dns_engine_t *engine, dns_config_zone_t *zone, void *conf, char *arg)
{
    dns_engine_param_t param;

    if (engine->eng_setarg != NULL) {
        param.ep_zone = NULL;
        param.ep_conf = conf;

        if (engine->eng_setarg(&param, arg) < 0)
            return -1;
    }

    return 0;
}
