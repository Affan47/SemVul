__find_stripe(struct r5conf *conf, sector_t sector,
					 short generation)
{
	struct stripe_head *sh;

	pr_debug("__find_stripe, sector %llu\n", (unsigned long long)sector);
	hlist_for_each_entry(sh, stripe_hash(conf, sector), hash)
		if (sh->sector == sector && sh->generation == generation)
			return sh;
	pr_debug("__stripe %llu not in cache\n", (unsigned long long)sector);
	return NULL;
}
