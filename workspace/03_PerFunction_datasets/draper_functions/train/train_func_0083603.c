proc_net_walker(sigar_net_connection_walker_t *walker,
                           sigar_net_connection_t *conn)
{
    net_conn_getter_t *getter =
        (net_conn_getter_t *)walker->data;

    if (getter->connlist) {
        SIGAR_NET_CONNLIST_GROW(getter->connlist);
        memcpy(&getter->connlist->data[getter->connlist->number++],
               conn, sizeof(*conn));
    }
    else {
        if ((getter->port == conn->local_port) &&
            (conn->remote_port == 0))
        {
            memcpy(getter->conn, conn, sizeof(*conn));
            return !SIGAR_OK;
        }
    }

    return SIGAR_OK;
}
