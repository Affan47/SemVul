apr_memcache_add_server(apr_memcache_t *mc, apr_memcache_server_t *ms)
{
    apr_status_t rv = APR_SUCCESS;

    if(mc->ntotal >= mc->nalloc) {
        return APR_ENOMEM;
    }

    mc->live_servers[mc->ntotal] = ms;
    mc->ntotal++;
    make_server_live(mc, ms);
    return rv;
}
