_tcpConnectionTable_container_init(tcpConnectionTable_interface_ctx *
                                   if_ctx)
{
    DEBUGMSGTL(("internal:tcpConnectionTable:_tcpConnectionTable_container_init", "called\n"));


    if_ctx->cache = netsnmp_cache_create(30,
                                         _cache_load, _cache_free,
                                         tcpConnectionTable_oid,
                                         tcpConnectionTable_oid_size);

    if (NULL == if_ctx->cache) {
        snmp_log(LOG_ERR, "error creating cache for tcpConnectionTable\n");
        return;
    }

    if_ctx->cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;

    tcpConnectionTable_container_init(&if_ctx->container, if_ctx->cache);
    if (NULL == if_ctx->container) {
        if_ctx->container =
            netsnmp_container_find("tcpConnectionTable:table_container");
        if (if_ctx->container)
        if_ctx->container->container_name = strdup("tcpConnectionTable");
    }
    if (NULL == if_ctx->container) {
        snmp_log(LOG_ERR, "error creating container in "
                 "tcpConnectionTable_container_init\n");
        return;
    }

    if (NULL != if_ctx->cache)
        if_ctx->cache->magic = (void *) if_ctx->container;
}
