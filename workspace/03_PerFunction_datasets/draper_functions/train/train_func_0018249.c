config_parse_root(dns_config_root_t *root, config_context_t *ctx)
{
    config_token_t tok;
    dns_config_zone_t *zone;

    for (;;) {
        if (config_get_token(&tok, ctx) < 0)
            return 0;

        if (tok.tok_code != CONFIG_TOKEN_STRING)
            return -1;

        if (strcmp(tok.tok_string, "zone") == 0) {
            if ((zone = calloc(1, sizeof(dns_config_zone_t))) == NULL) {
                plog(LOG_ERR, "%s: insufficient memory", MODULE);
                return -1;
            }

            if (dns_acl_init(&zone->z_slaves.zss_acl) < 0) {
                plog(LOG_ERR, "%s: dns_acl_init() failed", MODULE);
                config_free_zone(zone);
                return -1;
            }

            if (config_parse_clause(zone, ctx,
                                    (config_parse_head_t *) config_parse_zone_head,
                                    (config_parse_body_t *) config_parse_zone_body,
                                    zone) < 0) {
                config_free_zone(zone);
                return -1;
            }

            dns_list_push(&root->r_zone, &zone->z_elem);
            continue;
        }

        config_error_unexpected(&tok, ctx);
        return -1;
    }
}
