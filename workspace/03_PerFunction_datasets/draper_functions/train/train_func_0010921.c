cstate_cpumask_init(void)
{
	int cpu;

	cpu_notifier_register_begin();

	for_each_online_cpu(cpu)
		cstate_cpu_init(cpu);

	__perf_cpu_notifier(cstate_cpu_notifier);

	cpu_notifier_register_done();
}
