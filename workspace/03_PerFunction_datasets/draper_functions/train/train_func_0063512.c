us_rawnet_multi_rawnet_poll_incoming(
    us_rawnet_multi_t * self,
    time_t cur_time,
    int max_poll_count,
    void * context,
    void ( *handler )( us_rawnet_multi_t * self, int ethernet_port, void * context, uint8_t * buf, uint16_t len ) )
{
    int poll_count = 0;
    int zero_count = 0;
    for ( poll_count = 0; poll_count < max_poll_count; ++poll_count )
    {
        if ( us_rawnet_multi_receive( self, cur_time, context, handler ) == 0 )
        {
            if ( zero_count++ > 2 )
            {
                break;
            }
        }
    }
}
