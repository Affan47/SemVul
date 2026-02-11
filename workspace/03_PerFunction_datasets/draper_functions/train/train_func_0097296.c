node_proxy_cancel_all(void)
{
	GSList *sl;

	for (sl = sl_nodes; sl; sl = g_slist_next(sl)) {
		gnutella_node_t *n = sl->data;

		if (is_host_addr(n->proxy_addr)) {
			if (NODE_IS_WRITABLE(n))
				vmsg_send_proxy_cancel(n);
			n->proxy_addr = zero_host_addr;
			n->proxy_port = 0;
		}
	}

	pproxy_set_free_null(&proxies);
	proxies = pproxy_set_allocate(0);
	pdht_prox_publish_if_changed();
}
