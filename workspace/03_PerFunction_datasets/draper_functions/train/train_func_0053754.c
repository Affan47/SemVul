publish_cache_expired(cqueue_t *unused_cq, void *obj)
{
	publish_t *pb = obj;

	(void) unused_cq;
	publish_check(pb);

	pb->expire_ev = NULL;

	if (GNET_PROPERTY(dht_publish_debug))
		g_debug("DHT PUBLISH[%s] %s%s%s publish of %d value%s for %s expired",
			nid_to_string(&pb->pid),
			(pb->flags & PB_F_SUBORDINATE) ? "subordinate " : "",
			(pb->flags & PB_F_BACKGROUND) ? "background " : "",
			publish_type_to_string(pb->type),
			pb->cnt, 1 == pb->cnt ? "" : "s",
			kuid_to_hex_string(pb->key));

	publish_terminate(pb, PUBLISH_E_EXPIRED);
}
