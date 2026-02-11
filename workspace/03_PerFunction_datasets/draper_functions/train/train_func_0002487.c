dht_node_timed_out(knode_t *kn)
{
	knode_check(kn);


	if (!GNET_PROPERTY(is_inet_connected)) {
		if (GNET_PROPERTY(dht_debug)) {
			g_debug("DHT not connected to Internet, "
				"ignoring RPC timeout for %s",
				knode_to_string(kn));
		}
		return;
	}

	if (++kn->rpc_timeouts >= KNODE_MAX_TIMEOUTS) {
		dht_remove_timeouting_node(kn);
	} else {


		if (kn->flags & KNODE_F_SHUTDOWNING) {
			dht_set_node_status(kn, KNODE_PENDING);
		} else {
			dht_set_node_status(kn, KNODE_STALE);
		}
	}
}
