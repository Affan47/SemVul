dh_can_forward(dqhit_t *dh, mqueue_t *mq, bool test)
{
	const char *teststr = test ? "[test] " : "";

	g_assert(mq != NULL);


	if (
		mq_size(mq) > mq_hiwat(mq) &&
		(dh->hits_sent >= DH_THRESH_HITS || dh->hits_queued >= DH_MIN_HITS)
	) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %squeue size > hiwat, dropping", teststr);
		return DH_DROP_FC;
	}


	if (
		mq_is_swift_controlled(mq) &&
		(dh->hits_sent >= DH_MIN_HITS || dh->hits_queued >= DH_MIN_HITS)
	) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %squeue in SWIFT mode, dropping", teststr);
		return DH_DROP_FC;
	}


	if (
		mq_is_flow_controlled(mq) &&
		(
			(dh->hits_sent >= DH_MIN_HITS &&
		 	 dh->hits_queued >= 2 * DH_THRESH_HITS) ||
			(dh->hits_sent < DH_MIN_HITS &&
			 (dh->hits_sent + dh->hits_queued) >= DH_MIN_HITS + DH_THRESH_HITS)
		)
	) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %squeue in FLOWC mode, dropping", teststr);
		return DH_DROP_FC;
	}


	if (
		mq_size(mq) > mq_lowat(mq) &&
		dh->hits_sent >= DH_POPULAR_HITS &&
		dh->hits_queued >= (DH_MIN_HITS / 2)
	) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %squeue size > lowat, dropping", teststr);
		return DH_DROP_FC;
	}


	if (
		dh->hits_sent >= DH_POPULAR_HITS &&
		dh->hits_queued >= DH_MIN_HITS
	) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %senough hits queued, throttling", teststr);
		return DH_DROP_THROTTLE;
	}


	if (
		dh->hits_sent < DH_MAX_HITS &&
		dh->hits_queued > (DH_MIN_HITS / 2) &&
		(dh->hits_queued + dh->hits_sent) >= DH_MAX_HITS) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %senough queued, nearing max, throttling", teststr);
		return DH_DROP_THROTTLE;
	}


	if (dh->hits_sent >= DH_MAX_HITS && dh->hits_queued) {
		if (GNET_PROPERTY(dh_debug) > 19)
			g_debug("DH %smax sendable hits reached, throttling", teststr);
		return DH_DROP_THROTTLE;
	}


	{
		gnutella_node_t *n = mq_node(mq);

		if (NODE_IS_TRANSIENT(n) && mq_size(mq) > mq_lowat(mq)) {
			if (GNET_PROPERTY(dh_debug) > 19) {
				g_debug("DH %stransient target %s with %d bytes in queue",
					teststr, node_infostr(n), mq_size(mq));
			}
			return DH_DROP_TRANSIENT;
		}
	}

	if (GNET_PROPERTY(dh_debug) > 19)
		g_debug("DH %sforwarding", teststr);

	return DH_FORWARD;
}
