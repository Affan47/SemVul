cpu_stop_park(unsigned int cpu)
{
	struct cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);

	WARN_ON(!list_empty(&stopper->works));
}
