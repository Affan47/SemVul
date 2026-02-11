zs_register_cpu_notifier(void)
{
	int cpu, uninitialized_var(ret);

	cpu_notifier_register_begin();

	__register_cpu_notifier(&zs_cpu_nb);
	for_each_online_cpu(cpu) {
		ret = zs_cpu_notifier(NULL, CPU_UP_PREPARE, (void *)(long)cpu);
		if (notifier_to_errno(ret))
			break;
	}

	cpu_notifier_register_done();
	return notifier_to_errno(ret);
}
