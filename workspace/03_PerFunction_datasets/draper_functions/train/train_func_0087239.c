mem_cgroup_soft_reclaim(struct mem_cgroup *root_memcg,
				   struct zone *zone,
				   gfp_t gfp_mask,
				   unsigned long *total_scanned)
{
	struct mem_cgroup *victim = NULL;
	int total = 0;
	int loop = 0;
	unsigned long excess;
	unsigned long nr_scanned;
	struct mem_cgroup_reclaim_cookie reclaim = {
		.zone = zone,
		.priority = 0,
	};

	excess = soft_limit_excess(root_memcg);

	while (1) {
		victim = mem_cgroup_iter(root_memcg, victim, &reclaim);
		if (!victim) {
			loop++;
			if (loop >= 2) {


				if (!total)
					break;


				if (total >= (excess >> 2) ||
					(loop > MEM_CGROUP_MAX_RECLAIM_LOOPS))
					break;
			}
			continue;
		}
		total += mem_cgroup_shrink_node_zone(victim, gfp_mask, false,
						     zone, &nr_scanned);
		*total_scanned += nr_scanned;
		if (!soft_limit_excess(root_memcg))
			break;
	}
	mem_cgroup_iter_break(root_memcg, victim);
	return total;
}
