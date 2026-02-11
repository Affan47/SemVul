smp_stop_nmi_callback(unsigned int val, struct pt_regs *regs)
{

	if (raw_smp_processor_id() == atomic_read(&stopping_cpu))
		return NMI_HANDLED;

	stop_this_cpu(NULL);

	return NMI_HANDLED;
}
