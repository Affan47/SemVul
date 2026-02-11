hyperv_vector_handler(struct pt_regs *regs)
{
	struct pt_regs *old_regs = set_irq_regs(regs);

	entering_irq();
	inc_irq_stat(irq_hv_callback_count);
	if (vmbus_handler)
		vmbus_handler();

	exiting_irq();
	set_irq_regs(old_regs);
}
