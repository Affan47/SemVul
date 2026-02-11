sci_controller_error_handler(struct isci_host *ihost)
{
	u32 interrupt_status;

	interrupt_status =
		readl(&ihost->smu_registers->interrupt_status);

	if ((interrupt_status & SMU_ISR_QUEUE_SUSPEND) &&
	    sci_controller_completion_queue_has_entries(ihost)) {

		sci_controller_process_completions(ihost);
		writel(SMU_ISR_QUEUE_SUSPEND, &ihost->smu_registers->interrupt_status);
	} else {
		dev_err(&ihost->pdev->dev, "%s: status: %#x\n", __func__,
			interrupt_status);

		sci_change_state(&ihost->sm, SCIC_FAILED);

		return;
	}


	writel(0, &ihost->smu_registers->interrupt_mask);
}
