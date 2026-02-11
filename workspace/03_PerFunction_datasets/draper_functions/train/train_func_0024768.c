zone_statistics(struct zone *preferred_zone, struct zone *z, gfp_t flags)
{
	if (z->zone_pgdat == preferred_zone->zone_pgdat) {
		__inc_zone_state(z, NUMA_HIT);
	} else {
		__inc_zone_state(z, NUMA_MISS);
		__inc_zone_state(preferred_zone, NUMA_FOREIGN);
	}
	if (z->node == ((flags & __GFP_OTHER_NODE) ?
			preferred_zone->node : numa_node_id()))
		__inc_zone_state(z, NUMA_LOCAL);
	else
		__inc_zone_state(z, NUMA_OTHER);
}
