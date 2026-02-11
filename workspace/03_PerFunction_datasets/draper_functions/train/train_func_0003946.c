mwl_server_config_merge(apr_pool_t *pool, void *basev, void *overv)
{
    struct server_config *conf, *bconf, *oconf;

    conf  = apr_pcalloc(pool, sizeof(struct server_config));
    bconf = basev;
    oconf = overv;

    MERGE_PTR(auth_attr);
    MERGE_SET(authrule);
    MERGE_PTR(base);
    MERGE_PTR(binddn);
    MERGE_SET(debug);
    MERGE_SET(filter);
    MERGE_PTR(host);
    MERGE_PTR(keytab_path);
    MERGE_PTR_OTHER(keytab_principal, keytab_path);
    MERGE_INT(port);
    MERGE_PTR(separator);
    MERGE_SET(ssl);
    MERGE_PTR(tktcache);
    return conf;
}
