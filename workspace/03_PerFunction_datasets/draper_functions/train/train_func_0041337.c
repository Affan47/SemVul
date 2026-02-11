node_intuit_address(struct gnutella_node *n,  header_t *header)
{
	static const char *fields[] = {
		"Node",
		"Node-IPv6",
		"Listen-Ip",
		"X-My-Address",
	};
	uint i;

	for (i = 0; i < G_N_ELEMENTS(fields); i++) {
		const char *val = header_get(header, fields[i]);
		host_addr_t addr;
		uint16 port;

		if (val != NULL && parse_ip_port(val, NULL, &addr, &port)) {
			n->gnet_port = port;
			if (host_address_is_usable(addr))
				n->gnet_addr = addr;
			return TRUE;
		}
	}

	return FALSE;
}
