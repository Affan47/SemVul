broadcast_addr(struct ntb_network *nw,
               struct ntb_network_addr *addr)
{
        struct ntb_network_peer *peer;

        ntb_list_for_each(peer, &nw->peers, link) {
                if (peer->state == NTB_NETWORK_PEER_STATE_CONNECTED) {
                        ntb_connection_begin_addr(peer->connection);
                        ntb_connection_add_addr_address(peer->connection,
                                                        addr->advertise_time,
                                                        addr->stream,
                                                        addr->services,
                                                        &addr->address);
                        ntb_connection_end_addr(peer->connection);
                }
        }
}
