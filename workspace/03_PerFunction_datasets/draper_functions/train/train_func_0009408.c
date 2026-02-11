xen_vcpuop_shutdown(struct clock_event_device *evt)
{
	int cpu = smp_processor_id();

	if (HYPERVISOR_vcpu_op(VCPUOP_stop_singleshot_timer, cpu, NULL) ||
	    HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_timer, cpu, NULL))
		BUG();

	return 0;
}
