check_push_proxies(struct download *d, const header_t *header)
{
	const char *buf;
	const char *tok;
	size_t added = 0;
	strtok_t *st;

	download_check(d);


	buf = header_get(header, "X-FW-Node-Info");
	if (buf && check_fw_node_info(d->server, buf)) {
		d->server->attrs |= DLS_A_FW_SOURCE;
		return;
	}


	buf = header_get(header, "X-Push-Proxy");
	if (buf == NULL)
		buf = header_get(header, "X-Push-Proxies");
	if (buf == NULL)
		buf = header_get(header, "X-Pushproxies");

	if (buf == NULL)
		return;

	d->server->attrs |= DLS_A_FW_SOURCE;
	st = strtok_make_strip(buf);

	while ((tok = strtok_next(st, ","))) {
		host_addr_t addr;
		uint16 port;


		if (is_strcaseprefix(tok, "pptls="))
			continue;

		if (!string_to_host_addr_port(tok, NULL, &addr, &port))
			continue;

		if (is_private_addr(addr) || !host_is_valid(addr, port)) {
			g_message("host %s sent non-routable IP address %s as push-proxy",
				download_host_info(d), host_addr_port_to_string(addr, port));
		} else {
			if (add_proxy(d->server, addr, port))
				added++;
		}
	}

	strtok_free(st);

	if (added > 0)
		download_push_proxy_wakeup(d->server, TRUE, FALSE);
}
