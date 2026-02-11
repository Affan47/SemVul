dhcpv4_relay_send(struct dhcpv4_relay *relay, struct dhcpv4_packet *request, uint32_t server_id, const char *agent_circuit_id, const char *agent_remote_id)
{
	int n;
	int len = request->ptr - request->data;
	uint32_t giaddr = request->hdr->giaddr;
	struct dhcpv4_option *opt = NULL;
	uint32_t _server_id;

	if (!request->relay_agent && dhcpv4_packet_insert_opt82(request, agent_circuit_id, agent_remote_id))
		return -1;

	request->hdr->giaddr = relay->giaddr;

	if (server_id) {
		opt = dhcpv4_packet_find_opt(request, 54);
		if (opt) {
			_server_id = *(uint32_t *)opt->data;
			*(uint32_t *)opt->data = server_id;
		}
	}

	if (conf_verbose) {
		log_ppp_info2("send ");
		dhcpv4_print_packet(request, 1, log_ppp_info2);
	}

	len = request->ptr - request->data;
	n = write(relay->hnd.fd, request->data, len);

	request->hdr->giaddr = giaddr;

	if (opt)
		*(uint32_t *)opt->data = _server_id;

	if (n != len)
		return -1;

	return 0;
}
