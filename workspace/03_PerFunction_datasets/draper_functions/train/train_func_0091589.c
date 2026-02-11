gmsg_sendto_all(const GSList *sl, const void *msg, uint32 size)
{
	pmsg_t *mb = gmsg_to_pmsg(msg, size);

	gmsg_header_check(msg, size);

	if (GNET_PROPERTY(gmsg_debug) > 5 && gmsg_hops(msg) == 0)
		gmsg_dump(stdout, msg, size);

	for (; sl; sl = g_slist_next(sl)) {
		struct gnutella_node *dn = sl->data;
		if (!NODE_IS_ESTABLISHED(dn))
			continue;
		mq_tcp_putq(dn->outq, pmsg_clone(mb), NULL);
	}

	pmsg_free(mb);
}
