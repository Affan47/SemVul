opEQ(const InetAddr &other) const
{
    if (address_family!=other.address_family) return false;
    if (address_family==AF_INET)
    {
        return ipv4.s_addr == other.ipv4.s_addr;
    } else
    {
        return (IN6_ARE_ADDR_EQUAL(&(ipv6), &(other.ipv6)));
    }
}
