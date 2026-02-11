cfg_print_sockaddr(cfg_printer_t *pctx, const cfg_obj_t *obj) {
	isc_netaddr_t netaddr;
	in_port_t port;
	char buf[ISC_NETADDR_FORMATSIZE];

	isc_netaddr_fromsockaddr(&netaddr, &obj->value.sockaddr);
	isc_netaddr_format(&netaddr, buf, sizeof(buf));
	cfg_print_cstr(pctx, buf);
	port = isc_sockaddr_getport(&obj->value.sockaddr);
	if (port != 0) {
		cfg_print_chars(pctx, " port ", 6);
		cfg_print_rawuint(pctx, port);
	}
}
