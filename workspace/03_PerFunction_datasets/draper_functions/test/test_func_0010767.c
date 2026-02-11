handle_proxy_ack(struct gnutella_node *n,
	const struct vmsg *vmsg, const char *payload, size_t size)
{
	host_addr_t ha;
	uint16 port;

	if (VMSG_SHORT_SIZE(n, vmsg, size, vmsg->version < 2 ? 2 : 6))
		return;

	if (vmsg->version >= 2) {
		ha = host_addr_peek_ipv4(payload);
		payload += 4;
	} else {
		ha = n->addr;
	}

	port = peek_le16(payload);

	if (GNET_PROPERTY(vmsg_debug) > 2) {
		g_debug("VMSG got proxy ACK v%u from %s: proxy at %s",
			vmsg->version,
			node_infostr(n), host_addr_port_to_string(ha, port));
	}

	if (!host_is_valid(ha, port)) {
		g_warning("got improper address %s in %s from %s",
			host_addr_port_to_string(ha, port), vmsg->name, node_infostr(n));
		return;
	}
	if (hostiles_is_bad(ha)) {
		hostiles_flags_t flags = hostiles_check(ha);
		g_message("VMSG ignoring proxy ACK from hostile %s (%s): proxy at %s",
			node_infostr(n), hostiles_flags_to_string(flags),
			host_addr_port_to_string(ha, port));
		return;
	}

	node_proxy_add(n, ha, port);
}
