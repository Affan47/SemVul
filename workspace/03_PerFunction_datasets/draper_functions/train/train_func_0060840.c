dns_gethostbyname(void)
{
	fprintf(stdout, "Simple DNS resolve: ");
	dns_ok = 0;
	evdns_resolve_ipv4("www.monkey.org", 0, dns_gethostbyname_cb, NULL);
	event_dispatch();

	if (dns_ok == DNS_IPv4_A) {
		fprintf(stdout, "OK\n");
	} else {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}
}
