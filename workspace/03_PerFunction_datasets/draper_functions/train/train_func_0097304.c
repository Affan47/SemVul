aa_create_dir_config(apr_pool_t *p, char *path)
{
    apparmor_dir_cfg *newcfg = (apparmor_dir_cfg *) apr_pcalloc(p, sizeof(*newcfg));

    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
                 "aa_create_dir_cfg (%s)", path ? path : ":no path:");
    if (newcfg == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf,
                     "aa_create_dir_config: couldn't alloc dir config");
        return NULL;
    }
    newcfg->path = apr_pstrdup(p, path ? path : ":no path:");

    return newcfg;
}
