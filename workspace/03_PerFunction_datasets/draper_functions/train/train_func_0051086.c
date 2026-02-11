irq_remap_enable_fault_handling(void)
{
	if (!irq_remapping_enabled)
		return 0;

	if (!remap_ops->enable_faulting)
		return -ENODEV;

	return remap_ops->enable_faulting();
}
