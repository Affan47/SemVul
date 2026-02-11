start_shepherd_timer(void)
{
	int cpu;

	for_each_possible_cpu(cpu)
		INIT_DELAYED_WORK(per_cpu_ptr(&vmstat_work, cpu),
			vmstat_update);

	if (!alloc_cpumask_var(&cpu_stat_off, GFP_KERNEL))
		BUG();
	cpumask_copy(cpu_stat_off, cpu_online_mask);

	vmstat_wq = alloc_workqueue("vmstat", WQ_FREEZABLE|WQ_MEM_RECLAIM, 0);
	schedule_delayed_work(&shepherd,
		round_jiffies_relative(sysctl_stat_interval));
}
