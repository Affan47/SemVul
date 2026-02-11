resolve_route_for_connection( struct stat_context *ctx,
                struct tcp_connection *conn_p)
{
        struct ifinfo *iinfo_p;

        if ( conn_p->state == TCP_LISTEN )
                return;

        iinfo_p = get_ifinfo_by_name( ctx->iftab,
                        conn_p->metadata.ifname );
        if ( iinfo_p != NULL ) {
                if ( iinfo_p->routes == NULL ) {
                        WARN("No routes for interface %s \n", iinfo_p->ifname );
                } else {
                        conn_p->metadata.route = rtlist_find_info(
                                        iinfo_p->routes, conn_p );
                }
        }
        return;
}
