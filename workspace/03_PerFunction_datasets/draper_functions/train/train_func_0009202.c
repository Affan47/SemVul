qhit_send_node(void *data, size_t len, void *udata)
{
	gnutella_node_t *n = udata;
	gnutella_header_t *packet_head = data;
	uint ttl;

	if (GNET_PROPERTY(dbg) > 3) {
		g_debug("flushing query hit (%u entr%s, %u bytes sofar) to %s",
			(uint) found_file_count(),
			found_file_count() == 1 ? "y" : "ies",
			(uint) found_size(),
			node_addr(n));
	}

	g_assert(len <= INT_MAX);


	if (gnutella_header_get_hops(&n->header) == 0) {
		g_warning("qhit_send_node(): hops=0, bug in route_message()?");

		gnutella_header_set_hops(&n->header, 1);
	}

	ttl = gnutella_header_get_hops(&n->header) + 5U;
	ttl = MIN(ttl, GNET_PROPERTY(hard_ttl_limit));
	gnutella_header_set_ttl(packet_head, ttl);

	gmsg_sendto_one(n, data, len);
}
