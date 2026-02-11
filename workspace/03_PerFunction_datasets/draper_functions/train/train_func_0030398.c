uip_init(struct uip_stack *ustack, uint8_t ipv6_enabled)
{
	u8_t c;

	for (c = 0; c < UIP_LISTENPORTS; ++c)
		ustack->uip_listenports[c] = 0;
	for (c = 0; c < UIP_CONNS; ++c)
		ustack->uip_conns[c].tcpstateflags = UIP_CLOSED;
#if UIP_ACTIVE_OPEN
	ustack->lastport = 1024;
#endif

#if UIP_UDP
	for (c = 0; c < UIP_UDP_CONNS; ++c)
		ustack->uip_udp_conns[c].lport = 0;
#endif


#if UIP_FIXEDADDR == 0

#endif


	memset(&ustack->stats, 0, sizeof(ustack->stats));


	pthread_mutex_init(&ustack->lock, NULL);

	if (ipv6_enabled)
		ustack->enable_IPv6 = UIP_SUPPORT_IPv6_ENABLED;
	else
		ustack->enable_IPv6 = UIP_SUPPORT_IPv6_DISABLED;

	ustack->dhcpc = NULL;
	ustack->ndpc = NULL;
}
