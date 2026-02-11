get_rate_limit(struct nhrp_address *src,
					      struct nhrp_address *dst)
{
	unsigned int key;
	struct nhrp_rate_limit *e;
	struct hlist_node *n;

	key = nhrp_address_hash(src) ^ nhrp_address_hash(dst);
	key %= RATE_LIMIT_HASH_SIZE;

	hlist_for_each_entry(e, n, &rate_limit_hash[key], hash_entry) {
		if (nhrp_address_cmp(&e->src, src) == 0 &&
		    nhrp_address_cmp(&e->dst, dst) == 0)
			return e;
	}

	e = calloc(1, sizeof(struct nhrp_rate_limit));
	e->src = *src;
	e->dst = *dst;
	hlist_add_head(&e->hash_entry, &rate_limit_hash[key]);

	if (num_rate_limit_entries == 0) {
		ev_timer_init(&rate_limit_timer, prune_rate_limit_entries_cb,
			      RATE_LIMIT_PURGE_INTERVAL,
			      RATE_LIMIT_PURGE_INTERVAL);
		ev_timer_start(&rate_limit_timer);
	}

	num_rate_limit_entries++;

	return e;
}
