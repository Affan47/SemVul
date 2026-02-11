vmstat_cpuup_callback(struct notifier_block *nfb,
		unsigned long action,
		void *hcpu)
{
	long cpu = (long)hcpu;

	switch (action) {
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		refresh_zone_stat_thresholds();
		node_set_state(cpu_to_node(cpu), N_CPU);
		cpumask_set_cpu(cpu, cpu_stat_off);
		break;
	case CPU_DOWN_PREPARE:
	case CPU_DOWN_PREPARE_FROZEN:
		cancel_delayed_work_sync(&per_cpu(vmstat_work, cpu));
		cpumask_clear_cpu(cpu, cpu_stat_off);
		break;
	case CPU_DOWN_FAILED:
	case CPU_DOWN_FAILED_FROZEN:
		cpumask_set_cpu(cpu, cpu_stat_off);
		break;
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		refresh_zone_stat_thresholds();
		vmstat_cpu_dead(cpu_to_node(cpu));
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}
