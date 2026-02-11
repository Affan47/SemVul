merge_msrpc_config(apr_pool_t *p, void *basev, void *overridesv)
{
    proxy_msrpc_conf_t *new_c = apr_pcalloc(p, sizeof(proxy_msrpc_conf_t));
    proxy_msrpc_conf_t *base = (proxy_msrpc_conf_t *)basev;
    proxy_msrpc_conf_t *overrides = (proxy_msrpc_conf_t *)overridesv;

    new_c->enabled = (overrides->enabled_set == 0)
                     ? base->enabled
                     : overrides->enabled;
    if (overrides->user_agents) {
        new_c->user_agents = apr_array_copy_hdr(p, overrides->user_agents);
    }
    return new_c;
}
