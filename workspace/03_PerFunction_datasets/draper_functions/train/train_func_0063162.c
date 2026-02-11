us_rawnet_join_multicast( us_rawnet_context_t *self, const uint8_t multicast_mac[6] )
{
    bool r = false;
    struct packet_mreq mreq;
    struct sockaddr_ll saddr;
    if ( multicast_mac )
    {
        memset( &saddr, 0, sizeof( saddr ) );
        saddr.sll_family = AF_PACKET;
        saddr.sll_ifindex = self->m_interface_id;
        saddr.sll_pkttype = PACKET_MULTICAST;
        saddr.sll_protocol = htons( self->m_ethertype );
        if ( bind( self->m_fd, (struct sockaddr *)&saddr, sizeof( saddr ) ) >= 0 )
        {
            memset( &mreq, 0, sizeof( mreq ) );
            mreq.mr_ifindex = self->m_interface_id;
            mreq.mr_type = PACKET_MR_MULTICAST;
            mreq.mr_alen = 6;
            mreq.mr_address[0] = multicast_mac[0];
            mreq.mr_address[1] = multicast_mac[1];
            mreq.mr_address[2] = multicast_mac[2];
            mreq.mr_address[3] = multicast_mac[3];
            mreq.mr_address[4] = multicast_mac[4];
            mreq.mr_address[5] = multicast_mac[5];
            if ( setsockopt( self->m_fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof( mreq ) ) >= 0 )
            {
                r = true;
            }
            else
            {
                us_log_error( "us_rawnet_join_multicast setsockopt[SOL_SOCKET,PACKET_ADD_MEMBERSHIP] error %s",
                              strerror( errno ) );
            }
        }
        else
        {
            us_log_error( "us_rawnet_join_multicast bind error: %s", strerror( errno ) );
        }
    }
    return r;
}
