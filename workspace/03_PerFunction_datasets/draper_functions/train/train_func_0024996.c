get_default_epdisc(ep)
     struct epdisc *ep;
{
	char *p;
	struct hostent *hp;
	u_int32_t addr;

	FUNC_DEBUG("%s: %d\n", __FUNCTION__,__LINE__);


	p = get_first_ethernet();
	if (p != 0 && get_if_hwaddr(ep->value, p) >= 0) {
		ep->class = EPD_MAC;
		ep->length = 6;
		return 1;
	}


	hp = gethostbyname(hostname);
	if (hp != NULL) {
		addr = *(u_int32_t *)hp->h_addr;
		if (!bad_ip_adrs(addr)) {
			addr = ntohl(addr);
			if (!LOCAL_IP_ADDR(addr)) {
				ep->class = EPD_IP;
				set_ip_epdisc(ep, addr);
				return 1;
			}
		}
	}

	return 0;
}
