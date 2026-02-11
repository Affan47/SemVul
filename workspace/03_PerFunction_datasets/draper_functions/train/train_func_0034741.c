memcg_oom_wake_function(wait_queue_t *wait,
	unsigned mode, int sync, void *arg)
{
	struct mem_cgroup *wake_memcg = (struct mem_cgroup *)arg;
	struct mem_cgroup *oom_wait_memcg;
	struct oom_wait_info *oom_wait_info;

	oom_wait_info = container_of(wait, struct oom_wait_info, wait);
	oom_wait_memcg = oom_wait_info->memcg;

	if (!mem_cgroup_is_descendant(wake_memcg, oom_wait_memcg) &&
	    !mem_cgroup_is_descendant(oom_wait_memcg, wake_memcg))
		return 0;
	return autoremove_wake_function(wait, mode, sync, arg);
}
