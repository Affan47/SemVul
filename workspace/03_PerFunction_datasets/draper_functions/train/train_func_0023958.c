mem_cgroup_remove_from_trees(struct mem_cgroup *memcg)
{
	struct mem_cgroup_tree_per_zone *mctz;
	struct mem_cgroup_per_zone *mz;
	int nid, zid;

	for_each_node(nid) {
		for (zid = 0; zid < MAX_NR_ZONES; zid++) {
			mz = &memcg->nodeinfo[nid]->zoneinfo[zid];
			mctz = soft_limit_tree_node_zone(nid, zid);
			mem_cgroup_remove_exceeded(mz, mctz);
		}
	}
}
