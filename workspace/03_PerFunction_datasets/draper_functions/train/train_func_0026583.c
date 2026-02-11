stop_self(void *v)
{
	int cpu = smp_processor_id();


	load_cr3(swapper_pg_dir);


	set_cpu_online(cpu, false);

	HYPERVISOR_vcpu_op(VCPUOP_down, cpu, NULL);
	BUG();
}
