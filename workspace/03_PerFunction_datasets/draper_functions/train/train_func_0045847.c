us_rawnet_multi_route_add( us_rawnet_multi_t * self, uint8_t const mac[6], int last_seen_interface, time_t last_seen_time )
{
    int r = -1;


    if ( self->routing_table_count < US_RAWNET_MULTI_MAC_TABLE_SIZE )
    {

        us_rawnet_multi_mac_item_t *item = &self->routing_table[self->routing_table_count++];
        memcpy( item->mac, mac, 6 );
        item->last_seen_interface = last_seen_interface;
        item->last_seen_time = last_seen_time;
        item->last_changed_time = last_seen_time;

        qsort( self->routing_table, self->routing_table_count, sizeof( self->routing_table[0] ), us_rawnet_multi_mac_cmp );
        r = 0;
    }
    return r;
}
