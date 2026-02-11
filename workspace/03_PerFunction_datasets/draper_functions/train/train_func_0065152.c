ipcp_clear_addrs(unit, ouraddr, hisaddr)
    int unit;
    u_int32_t ouraddr;
    u_int32_t hisaddr;
{
    if (proxy_arp_set[unit]) {
	cifproxyarp(unit, hisaddr);
	proxy_arp_set[unit] = 0;
    }
    if (default_route_set[unit]) {
	cifdefaultroute(unit, ouraddr, hisaddr);
	default_route_set[unit] = 0;
    }
    cifaddr(unit, ouraddr, hisaddr);
}
