ntb_netaddress_to_native(const struct ntb_netaddress *address,
                         struct ntb_netaddress_native *native)
{
        if (!memcmp(address->host, ipv4_magic, sizeof ipv4_magic)) {
                ntb_netaddress_to_native_ipv4(address, &native->sockaddr_in);
                native->length = sizeof native->sockaddr_in;
        } else {
                ntb_netaddress_to_native_ipv6(address, &native->sockaddr_in6);
                native->length = sizeof native->sockaddr_in6;
        }
}
