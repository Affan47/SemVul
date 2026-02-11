webkdc_config_merge(apr_pool_t *pool, void *basev, void *overv)
{
    struct config *conf, *bconf, *oconf;

    conf  = apr_pcalloc(pool, sizeof(struct config));
    bconf = basev;
    oconf = overv;

    MERGE_PTR(identity_acl_path);
    MERGE_PTR(keyring_path);
    MERGE_PTR(keytab_path);
    MERGE_PTR_OTHER(keytab_principal, keytab_path);
    MERGE_PTR(token_acl_path);
    MERGE_PTR(userinfo_config);
    MERGE_PTR(userinfo_principal);
    MERGE_SET(userinfo_timeout);
    MERGE_SET(userinfo_ignore_fail);
    MERGE_SET(debug);
    MERGE_SET(keyring_auto_update);
    MERGE_SET(key_lifetime);
    MERGE_SET(login_time_limit);
    MERGE_SET(proxy_lifetime);
    MERGE_INT(service_lifetime);
    MERGE_SET(token_max_ttl);
    MERGE_ARRAY(permitted_realms);
    MERGE_ARRAY(kerberos_factors);


    MERGE_ARRAY(local_realms);

    return conf;
}
