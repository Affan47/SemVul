p_rtnodex( struct route_entry *rp )
{
    get_ifname(rp->ifname, rp->ifNumber);
    if (rp->af == AF_INET) {
        struct sockaddr_in *sin = (struct sockaddr_in *)&rp->dst;
        printf("%-*s ",
            WID_DST(AF_INET),
                (sin->sin_addr.s_addr == INADDR_ANY) ? "default" :
                (rp->mask == 32 ?
                    routexname(&rp->dst) :
                    netxname(&rp->dst, rp->mask)));
    }
    else if (rp->af == AF_INET6) {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&rp->dst;
        struct in6_addr in6_addr_any = IN6ADDR_ANY_INIT;
        printf("%-*s ",
            WID_DST(AF_INET6),
                memcmp(&sin6->sin6_addr, &in6_addr_any, sizeof(in6_addr_any)) == 0 ? "default" :
                (rp->mask == 128 ?
                    routexname(&rp->dst) :
                    netxname(&rp->dst, rp->mask)));
    }
    printf("%-*s %-6.6s  %s",
        WID_GW(rp->af),
        1 ? routexname(&rp->hop) : "*",
        s_rtflagsx(rp), rp->ifname);
    if ((rp->set_bits & SET_AS) && rp->as != 0)
        printf(" (AS %d)", rp->as);
    printf("\n");
}
