send_PACKET( n2n_edge_t * eee,
                        n2n_mac_t dstMac,
                        const uint8_t * pktbuf,
                        size_t pktlen )
{
    int dest;
    ssize_t s;
    n2n_sock_str_t sockbuf;
    n2n_sock_t destination;
    struct sockaddr_in destsock;


    dest = find_peer_destination(eee, dstMac, &destination);

    if ( dest )
    {
        ++(eee->tx_p2p);
    }
    else
    {
        ++(eee->tx_sup);
    }

    fill_sockaddr( (struct sockaddr *)&destsock, sizeof(destsock), &destination );

    traceEvent( TRACE_INFO, "send_PACKET to %s", sock_to_cstr( sockbuf, &destination ) );

    s = sendto_sock( eee->udp_sock, pktbuf, pktlen, &destination );

    return 0;
}
