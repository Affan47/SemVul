memcg_initialize (xcgroup_ns_t *ns, xcgroup_t *cg,
			     char *path, uint64_t mem_limit, uid_t uid,
			     gid_t gid, uint32_t notify)
{
	uint64_t mlb = mem_limit_in_bytes (mem_limit);
	uint64_t mls = swap_limit_in_bytes  (mem_limit);

	if (xcgroup_create (ns, cg, path, uid, gid) != XCGROUP_SUCCESS)
		return -1;

	cg->notify = notify;

	if (xcgroup_instanciate (cg) != XCGROUP_SUCCESS) {
		xcgroup_destroy (cg);
		return -1;
	}

	xcgroup_set_param (cg, "memory.use_hierarchy","1");


	if ( ! constrain_ram_space )
		mlb = mls;
	xcgroup_set_uint64_param (cg, "memory.limit_in_bytes", mlb);


	if ( constrain_swap_space ) {
		xcgroup_set_uint64_param (cg, "memory.memsw.limit_in_bytes",
					  mls);
		info ("task/cgroup: %s: alloc=%luMB mem.limit=%luMB "
		      "memsw.limit=%luMB", path,
		      (unsigned long) mem_limit,
		      (unsigned long) mlb/(1024*1024),
		      (unsigned long) mls/(1024*1024));
	} else {
		info ("task/cgroup: %s: alloc=%luMB mem.limit=%luMB "
		      "memsw.limit=unlimited", path,
		      (unsigned long) mem_limit,
		      (unsigned long) mlb/(1024*1024));
	}

	return 0;
}
