node_tx_flowc_left(gnutella_node_t *n, bool sent, void *unused_arg)
{
	(void) unused_arg;


	if (n != NULL && n->outq != NULL && !mq_is_flow_controlled(n->outq)) {
		bio_source_t *bio = mq_bio(n->outq);


		bio_set_favour(bio, FALSE);
		bio_add_allocated(bio, mq_tx_pending(n->outq));
	}

	if (GNET_PROPERTY(node_debug) > 4) {
		g_debug("NODE %s query-enabling Hops-Flow to %s, %s%s%s",
			sent ? "sent" : "discarded",
			NULL == n ? "gone node" : node_infostr(n),
			(NULL == n || NULL == n->outq) ? "queue gone" : mq_info(n->outq),
			(NULL == n || NULL == n->outq) ? "" : " TX pending=",
			(NULL == n || NULL == n->outq) ?
				"" : uint_to_string(mq_tx_pending(n->outq))
		);
	}
}
