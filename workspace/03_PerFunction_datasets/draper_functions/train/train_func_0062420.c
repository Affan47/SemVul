is_ethMulticast( const void * buf, size_t bufsize )
{
    int retval = 0;


    if ( bufsize >= sizeof(ether_hdr_t) )
    {

        ether_hdr_t eh;
        memcpy( &eh, buf, sizeof(ether_hdr_t) );

        if ( (0x01 == eh.dhost[0]) &&
             (0x00 == eh.dhost[1]) &&
             (0x5E == eh.dhost[2]) &&
             (0 == (0x80 & eh.dhost[3])) )
        {
            retval = 1;
        }
    }
    return retval;
}
