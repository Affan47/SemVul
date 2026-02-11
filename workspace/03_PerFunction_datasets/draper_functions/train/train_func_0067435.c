net_stat_port_walker(sigar_net_connection_walker_t *walker,
                                sigar_net_connection_t *conn)
{
    net_stat_port_getter_t *getter =
        (net_stat_port_getter_t *)walker->data;
    sigar_net_stat_t *netstat = getter->netstat;

    if (conn->type == SIGAR_NETCONN_TCP) {
        if (conn->local_port == getter->port) {
            netstat->all_inbound_total++;

            if (sigar_net_address_equals(getter->address,
                                         &conn->local_address) == SIGAR_OK)
            {
                netstat->tcp_inbound_total++;
            }
        }
        else if (conn->remote_port == getter->port) {
            netstat->all_outbound_total++;

            if (sigar_net_address_equals(getter->address,
                                         &conn->remote_address) == SIGAR_OK)
            {
                netstat->tcp_outbound_total++;
            }
        }
        else {
            return SIGAR_OK;
        }

        netstat->tcp_states[conn->state]++;
    }
    else if (conn->type == SIGAR_NETCONN_UDP) {

    }

    return SIGAR_OK;
}
