mem_cgroup_read_events(struct mem_cgroup *memcg,
					    enum mem_cgroup_events_index idx)
{
	unsigned long val = 0;
	int cpu;

	for_each_possible_cpu(cpu)
		val += per_cpu(memcg->stat->events[idx], cpu);
	return val;
}
