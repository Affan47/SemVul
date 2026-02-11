us_rawnet_multi_send_reply_all( us_rawnet_multi_t * self,
                                    uint8_t * data,
                                    uint16_t len,
                                    uint8_t const * data1,
                                    uint16_t len1,
                                    uint8_t const * data2,
                                    uint16_t len2 )
{

    int frames_sent = 0;
    int i;
    uint8_t buf[1514];
    int interface_to_send_to = -1;
    uint16_t total_len = len + len1 + len2;


    memcpy( buf, data, len );
    if ( data1 && len1 )
    {
        memcpy( buf + len, data1, len1 );
    }
    if ( data2 && len2 )
    {
        memcpy( buf + len + len1, data2, len2 );
    }


    interface_to_send_to = us_rawnet_multi_route_find( self, &buf[0] );
    if ( interface_to_send_to == -1 )
    {

        for ( i = 0; i < self->ethernet_port_count; ++i )
        {
            ssize_t sent = us_rawnet_send( &self->ethernet_ports[i], &buf[6], &buf[14], total_len - 14 );
            if ( sent > 0 )
            {
                frames_sent++;
            }
        }
    }
    else
    {

        ssize_t sent = us_rawnet_send( &self->ethernet_ports[interface_to_send_to], &buf[6], &buf[14], total_len - 14 );
        if ( sent > 0 )
        {
            frames_sent++;
        }
    }

    return frames_sent;
}
