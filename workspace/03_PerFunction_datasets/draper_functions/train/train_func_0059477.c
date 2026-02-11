nss_config_global_create(server_rec *s)
{
    apr_pool_t *pool = s->process->pool;
    SSLModConfigRec *mc;
    void *vmc;

    apr_pool_userdata_get(&vmc, SSL_MOD_CONFIG_KEY, pool);
    if (vmc) {
        return vmc;
    }


    mc = (SSLModConfigRec *)apr_palloc(pool, sizeof(*mc));
    mc->pPool = pool;


    mc->nInitCount                  = 0;
    mc->pCertificateDatabase        = NULL;
    mc->pDBPrefix                   = NULL;
    mc->session_cache_size          = UNSET;
    mc->session_cache_timeout       = UNSET;
    mc->ssl3_session_cache_timeout  = UNSET;
    mc->pphrase_dialog_helper       = NULL;
    mc->pphrase_dialog_path         = NULL;
    mc->aRandSeed                   = apr_array_make(pool, 4,
                                                     sizeof(ssl_randseed_t));

    apr_pool_userdata_set(mc, SSL_MOD_CONFIG_KEY,
                          apr_pool_cleanup_null,
                          pool);

    return mc;
}
