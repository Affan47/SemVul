drain_all_stock(struct mem_cgroup *root_memcg)
{
	int cpu, curcpu;


	if (!mutex_trylock(&percpu_charge_mutex))
		return;

	get_online_cpus();
	curcpu = get_cpu();
	for_each_online_cpu(cpu) {
		struct memcg_stock_pcp *stock = &per_cpu(memcg_stock, cpu);
		struct mem_cgroup *memcg;

		memcg = stock->cached;
		if (!memcg || !stock->nr_pages)
			continue;
		if (!mem_cgroup_is_descendant(memcg, root_memcg))
			continue;
		if (!test_and_set_bit(FLUSHING_CACHED_CHARGE, &stock->flags)) {
			if (cpu == curcpu)
				drain_local_stock(&stock->work);
			else
				schedule_work_on(cpu, &stock->work);
		}
	}
	put_cpu();
	put_online_cpus();
	mutex_unlock(&percpu_charge_mutex);
}
