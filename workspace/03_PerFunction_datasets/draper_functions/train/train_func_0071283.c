found_net_addr(struct east_state *es, unsigned char *a)
{
	unsigned char ip[4];

	memcpy(ip, a, 3);
	if (!ip[0]) {
		printf("Shit, prolly got a lame dhcp dude\n");
		exit(1);
	}

	ip[3] = 123;
	memcpy(&es->es_myip, ip, 4);
	printf("My IP %s\n", inet_ntoa(es->es_myip));
	set_tap_ip(es);

	ip[3] = 1;
	memcpy(&es->es_rtrip, ip, 4);
	printf("Rtr IP %s\n", inet_ntoa(es->es_rtrip));
	es->es_astate = AS_FIND_RTR_MAC;
}
