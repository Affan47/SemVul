node_proxy_add(gnutella_node_t *n, const host_addr_t addr, uint16 port)
{
	if (!(n->flags & NODE_F_PROXY)) {
		g_warning("got spurious push-proxy ack from %s", node_infostr(n));
		return;
	}

	n->flags &= ~NODE_F_PROXY;

	if (!GNET_PROPERTY(is_firewalled)) {
		g_warning("ignoring push-proxy ack from %s: no longer firewalled",
			node_infostr(n));
		return;
	}


	if (
		GNET_PROPERTY(node_debug) &&
		is_host_addr(n->gnet_addr) &&
		(!host_addr_equal(addr, n->gnet_addr) || port != n->gnet_port)
	)
		g_warning("push-proxy address %s from %s does not match "
			"its advertised node address %s:%u",
			host_addr_port_to_string(addr, port), node_infostr(n),
			host_addr_to_string(n->gnet_addr), n->gnet_port);

	if (!host_addr_equal(addr, n->addr)) {
		g_warning("push-proxy address %s from %s not on same host",
			host_addr_port_to_string(addr, port), node_infostr(n));
		if (is_host_addr(n->gnet_addr) && host_addr_equal(addr, n->gnet_addr))
			g_warning("however address %s matches the advertised node address",
				host_addr_port_to_string(addr, port));
	}

	n->proxy_addr = addr;
	n->proxy_port = port;

	pproxy_set_add(proxies, addr, port);
	pdht_prox_publish_if_changed();
	node_fire_node_flags_changed(n);
}
