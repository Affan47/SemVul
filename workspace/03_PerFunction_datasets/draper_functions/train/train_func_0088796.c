arcnet_encap_print(u_char arctype, const u_char *p,
    u_int length, u_int caplen)
{
	switch (arctype) {

	case ARCTYPE_IP_OLD:
	case ARCTYPE_IP:
	        ip_print(gndo, p, length);
		return (1);

#ifdef INET6
	case ARCTYPE_INET6:
		ip6_print(gndo, p, length);
		return (1);
#endif

	case ARCTYPE_ARP_OLD:
	case ARCTYPE_ARP:
	case ARCTYPE_REVARP:
		arp_print(gndo, p, length, caplen);
		return (1);

	case ARCTYPE_ATALK:
		if (vflag)
			fputs("et1 ", stdout);
		atalk_print(p, length);
		return (1);

	case ARCTYPE_IPX:
		ipx_print(p, length);
		return (1);

	default:
		return (0);
	}
}
