us_rawnet_multi_join_multicast( us_rawnet_multi_t * self, uint8_t const mac[6] )
{
    int i;
    for ( i = 0; i < self->ethernet_port_count; ++i )
    {
        us_rawnet_join_multicast( &self->ethernet_ports[i], (uint8_t *)mac );
    }
}
