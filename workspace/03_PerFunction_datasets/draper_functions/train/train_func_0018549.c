is_multi_broadcast(const uint8_t * dest_mac) {

       int is_broadcast = ( memcmp(broadcast_addr, dest_mac, 6) == 0 );
       int is_multicast = ( memcmp(multicast_addr, dest_mac, 3) == 0 );
       int is_ipv6_multicast = ( memcmp(ipv6_multicast_addr, dest_mac, 2) == 0 );

       return is_broadcast || is_multicast || is_ipv6_multicast;

}
