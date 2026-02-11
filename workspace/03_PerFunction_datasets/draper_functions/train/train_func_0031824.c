cproxy_http_request(struct cproxy *cp)
{
	struct http_async *handle;
	char path[128];

	cproxy_check(cp);
	g_assert(NULL == cp->udp_ev);

	concat_strings(path, sizeof path,
		"/gnutella/push-proxy?ServerId=", guid_base32_str(cp->guid),
		tls_enabled() ? "&tls=true" : "",
		(void *) 0);


	handle = http_async_get_addr(path, cp->addr, cp->port,
		cproxy_http_header_ind, NULL, cproxy_http_error_ind);

	if (handle == NULL) {
		if (GNET_PROPERTY(download_debug)) {
			g_warning("can't connect to push-proxy %s for GUID %s: %s",
				host_addr_port_to_string(cp->addr, cp->port),
				guid_hex_str(cp->guid),
				http_async_strerror(http_async_errno));
		}
		download_proxy_failed(cp->d);
		return;
	}

	cp->http_handle = handle;
	cp->state = http_async_state(handle);


	http_async_set_opaque(handle, cp, NULL);
	http_async_set_op_get_request(handle, cproxy_build_request);
	http_async_set_op_headsent(handle, cproxy_sent_request);
	http_async_set_op_gotreply(handle, cproxy_got_reply);
	http_async_on_state_change(handle, cproxy_http_newstate);
}
