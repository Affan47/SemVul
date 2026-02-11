isci_intx_isr(int vec, void *data)
{
	irqreturn_t ret = IRQ_NONE;
	struct isci_host *ihost = data;

	if (sci_controller_isr(ihost)) {
		writel(SMU_ISR_COMPLETION, &ihost->smu_registers->interrupt_status);
		tasklet_schedule(&ihost->completion_tasklet);
		ret = IRQ_HANDLED;
	} else if (sci_controller_error_isr(ihost)) {
		spin_lock(&ihost->scic_lock);
		sci_controller_error_handler(ihost);
		spin_unlock(&ihost->scic_lock);
		ret = IRQ_HANDLED;
	}

	return ret;
}
