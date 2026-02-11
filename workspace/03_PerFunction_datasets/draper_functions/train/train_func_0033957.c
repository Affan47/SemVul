isci_msix_isr(int vec, void *data)
{
	struct isci_host *ihost = data;

	if (sci_controller_isr(ihost))
		tasklet_schedule(&ihost->completion_tasklet);

	return IRQ_HANDLED;
}
