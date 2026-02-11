dns_engine_notify(dns_config_zone_t *zone, struct sockaddr *remote, dns_tls_t *tls)
{
    int result = -1;
    dns_engine_t *engine;
    dns_engine_param_t param;
    dns_config_zone_engine_t *ze;

    ze = (dns_config_zone_engine_t *) dns_list_head(&zone->z_search.zs_engine);
    while (ze != NULL) {
        engine = (dns_engine_t *) ze->ze_engine;
        if (engine->eng_notify != NULL) {
            plog(LOG_DEBUG, "%s: notify \"%s\" engine", MODULE, engine->eng_name);

            param.ep_zone = zone;
            param.ep_conf = ze->ze_econf;

            if (engine->eng_notify(&param, remote, tls) >= 0)
                result = 0;
        }

        ze = (dns_config_zone_engine_t *) dns_list_next(&zone->z_search.zs_engine, &ze->ze_elem);
    }

    return result;
}
