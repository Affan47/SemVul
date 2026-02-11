xen_hvm_smp_init(void)
{
	if (!xen_have_vector_callback)
		return;
	smp_ops.smp_prepare_cpus = xen_hvm_smp_prepare_cpus;
	smp_ops.smp_send_reschedule = xen_smp_send_reschedule;
	smp_ops.cpu_up = xen_hvm_cpu_up;
	smp_ops.cpu_die = xen_cpu_die;
	smp_ops.send_call_func_ipi = xen_smp_send_call_function_ipi;
	smp_ops.send_call_func_single_ipi = xen_smp_send_call_function_single_ipi;
	smp_ops.smp_prepare_boot_cpu = xen_smp_prepare_boot_cpu;
}
