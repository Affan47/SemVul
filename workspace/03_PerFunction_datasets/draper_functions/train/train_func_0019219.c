gmsg_sendto_one(struct gnutella_node *n, const void *msg, uint32 size)
{
	if (!NODE_IS_WRITABLE(n))
		return;

	gmsg_header_check(msg, size);

	if (GNET_PROPERTY(gmsg_debug) > 5 && gmsg_hops(msg) == 0)
		gmsg_dump(stdout, msg, size);


	if (NODE_IS_UDP(n)) {
		pmsg_t *mb;
		gnet_host_t to;

		gnet_host_set(&to, n->addr, n->port);

		if (GNET_PROPERTY(guess_server_debug) > 19) {
			g_debug("GUESS sending local hit (%s) for #%s to %s",
				NODE_CAN_SR_UDP(n) ? "reliably" :
				NODE_CAN_INFLATE(n) ? "possibly deflated" : "uncompressed",
				guid_hex_str(gnutella_header_get_muid(msg)), node_infostr(n));
		}

		if (NODE_CAN_SR_UDP(n)) {
			mb = gmsg_to_pmsg(msg, size);
			pmsg_mark_reliable(mb);
		} else {
			mb = NODE_CAN_INFLATE(n) ?
				gmsg_to_deflated_pmsg(msg, size) :
				gmsg_to_pmsg(msg, size);
		}

		mq_udp_putq(n->outq, mb, &to);
	} else {
		mq_tcp_putq(n->outq, gmsg_to_pmsg(msg, size), NULL);
	}
}
